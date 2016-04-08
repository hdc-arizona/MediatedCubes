#include "DimAddress.h"

#include <numeric>
#include <iterator>

DimAddress::DimAddress(std::string key) : key(key) { }

std::vector<std::string>
DimAddress::prefixes() {
	std::vector<std::string> prefixes(key.size() + 1);

	for(std::string::size_type i = 0; i <= key.size(); i++)
		prefixes[i] = key.substr(0, i);

	return prefixes;
}

std::string DimAddress::exact() {
	return key;
}

std::ostream &operator<<(std::ostream & o, DimAddress const& d) {
	o << "DimAddress(";
	std::copy(d.key.begin(), d.key.end(), std::ostream_iterator<char>(o, ","));
	o << ")";
	return o;
}
