#include "Address.h"

#include <iostream>
#include <algorithm>
#include <iterator>

Address::Address(std::vector<DimAddress> addresses) : addresses(addresses) {}

std::vector<std::vector<std::string>>
Address::prefixes() {

	std::vector<std::vector<std::string>> partials = {{}};
	for(auto address : addresses) {
		std::vector<std::vector<std::string>> temp;
		for(auto s : address.prefixes()) {
			for(auto p : partials) {
				p.push_back(s);
				temp.push_back(p);
			}
		}
		partials.swap(temp);
	}

	return partials;
}

std::vector<std::string>
Address::exact() {
	std::vector<std::string> out;
	for(auto a : addresses)
		out.push_back(a.exact());
	return out;
}

std::ostream &operator<<(std::ostream & o, Address const& a) {
	o << "Address(";
	std::copy(a.addresses.begin(), a.addresses.end(), 
			std::ostream_iterator<DimAddress>(o, ","));
	o << ")";
	return o;
}
