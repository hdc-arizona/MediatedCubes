#include "DimAddress.h"

#include <numeric>
#include <iostream>
#include <iterator>
#include <cassert>

DimAddress::DimAddress(std::string key) : key(key) { }

/*
 * To support ANY aggregation on a 1-dim address over { 0, 1 } of depth k, we
 * need to be able to uniquely encode any string over the alphabet { 0, 1, * }
 * of length up to k, which means that we need 3^k possible values. We might
 * want 25-level quadtrees, hence uint64_t.
 *
 * These contribute to the size of the keys in the MediatedCube
 * address_to_prefix table (and there are a lot of keys!), so:
 *
 * - If we change to a more compact representation of an Address (sequence of
 *   DimAddress), then it would make sense to change this to smaller types when
 *   possible.
 *
 * - If you only want prefixes and not arbitrary addresses, you only need 32
 *   bits (5 for how long the prefix is, 27 for the pattern itself).
 *
 * Now, how do we actually map { w in { 0, 1, * }, |w| <= k } to uint64_t?
 * For simplicity, we limit the maximum address length lower than we
 * have to and just concatentate the prefix with the prefix length.
 */
uint64_t compute_prefix(std::string k, uint32_t prefix_len) {
	assert(prefix_len <= k.size());
	assert(k.size() < 32);

	std::string prefix = k.substr(0, prefix_len);

	size_t len = 0;
	uint64_t path = prefix_len > 0 ? stol(prefix, &len, 2) : 0;
	assert(len == prefix.size());

	return (path << 32) | prefix_len;
}

std::vector<uint64_t>
DimAddress::prefixes() {
	std::vector<uint64_t> prefixes;
	for(size_t i = 0; i <= key.size(); i++)
		prefixes.push_back(compute_prefix(key, i));

	return prefixes;
}

uint64_t DimAddress::exact() {
	return compute_prefix(key, key.size());
}

std::ostream &operator<<(std::ostream & o, DimAddress const& d) {
	return o << "DimAddress(" << d.key << ")";
}
