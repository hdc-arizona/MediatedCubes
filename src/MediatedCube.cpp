#include "MediatedCube.h"

#include <algorithm>
#include <cassert>
#include <iostream>

MediatedCube::MediatedCube() : id(0), address_to_witness(), witness_to_data() { }

void MediatedCube::add(Address a, summary_type value) {
	id_type current_id = id++;

	/* 
	 * Group new prefixes by the witness they currently point to. Inserting
	 * extra keys in address_to_witness isn't an issue here because by the end 
	 * of add() they all have non-empty witnesses as values anyway (see lookup 
	 * for an explanation of the potential problem).
	 */
	std::unordered_map<witness_type, std::vector<prefix_sequence>> new_prefixes;
	for(auto const& prefix : a.prefixes())
		new_prefixes[address_to_witness[prefix]].push_back(prefix);

	for(auto const& pair : new_prefixes) {
		witness_type const& witness = pair.first;
		uint32_t count = pair.second.size();

		auto const& current_data = witness_to_data[witness];

		auto hasher_copy = current_data.hasher;
		hasher_copy.update(current_id);
		witness_type new_witness = hasher_copy.digest();

		uint32_t old_refcount = current_data.refcount;
		assert((old_refcount > 0 || witness == witness_type()) && "Ref count bug");

		summary_type old_value = current_data.summary;

		if(old_refcount > 0) {
			if(old_refcount == count) {
				witness_to_data.erase(witness);
			} else {
				assert(old_refcount > count && "Ref count bug");
				witness_to_data[witness].refcount -= count;
			}
		}

		assert(witness_to_data.count(new_witness) == 0 && "Hash collision?!?");

		witness_to_data[new_witness] = {
			old_value + value, 
			hasher_copy, 
			count
		};

		for(auto const& prefix : pair.second)
			address_to_witness[prefix] = new_witness;
	}
}

MediatedCube::summary_type MediatedCube::lookup(Address a) {
	/*
	 * We would like to just do
	 *
	 *	return witness_to_summary[address_to_witness[a.exact()]];
	 *
	 * But unordered_map inserts a default-constructed value whenever we use 
	 * operator[] and miss, so this means that over time we might accumulate 
	 * many keys in address_to_witness that all point to witness().
	 *
	 * This solution does a single hash table lookup and doesn't leak memory.
	 * It's also ugly, but oh well.
	 */
	auto iter = address_to_witness.find(a.exact());
	return (iter != address_to_witness.end()) 
		? witness_to_data[iter->second].summary
		: summary_type();
}

std::tuple<int, int>
MediatedCube::size_summary() {
	return std::make_tuple(address_to_witness.size(), 
			witness_to_data.size());
}

void
MediatedCube::print_address_to_witness_table() {
	for(auto x : address_to_witness) {
		std::cout << x.first 
			<< " -> " << x.second 
			<< " -> " << witness_to_data[x.second].hasher.hexdigest()
			<< " (" << witness_to_data[x.second].summary << ")"
			<< std::endl;
	}
}
