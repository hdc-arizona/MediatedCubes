#include "DimAddress.h"

#include <numeric>
#include <iostream>
#include <iterator>

DimAddress::DimAddress(std::string key) : key("1" + key) { }

std::vector<uint64_t>
DimAddress::prefixes() {
	std::vector<uint64_t> prefixes(key.size());

	size_t len;
	uint64_t x = stol(key, &len, 2);

	for(std::string::size_type i = 0; i < key.size(); i++) {
		prefixes[i] = (((x >> i) & 0xFFFFFFFF) << 32 ) | (key.size() - i);
	}

	return prefixes;
}

uint64_t DimAddress::exact() {
	uint64_t x = stol(key, 0, 2);
	return (x << 32 ) | key.size();
}

std::ostream &operator<<(std::ostream & o, DimAddress const& d) {
	o << "DimAddress(";
	std::copy(d.key.begin(), d.key.end(), std::ostream_iterator<char>(o, ","));
	o << ")";
	return o;
}
