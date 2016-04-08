#pragma once

#include <unordered_map>

#include "Hasher.h"
#include "Address.h"

class MediatedCube {

public:
	typedef std::vector<std::string> prefix_sequence;
	typedef std::vector<uint8_t> witness_type;

	typedef Hasher hasher_type;
	typedef uint32_t summary_type;
	typedef uint32_t refcount_type;

	typedef std::map<prefix_sequence, witness_type>::size_type id_type;

	typedef struct witness_data {
		summary_type summary;
		hasher_type hasher;
		refcount_type refcount;

		witness_data() = default;
		witness_data(witness_data const & other) = default;
		witness_data(summary_type s, hasher_type h, refcount_type r) 
			: summary(s), hasher(h), refcount(r) {}
	} witness_data;


	MediatedCube();

	void add(Address a, summary_type value);
	summary_type lookup(Address a);

	std::tuple<int, int> size_summary();
	void print_address_to_witness_table();

private:
	id_type id;

	std::unordered_map<prefix_sequence, witness_type> address_to_witness;
	std::unordered_map<witness_type, witness_data> witness_to_data; 
};

