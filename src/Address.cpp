#include "Address.h"

#include <iostream>
#include <algorithm>
#include <iterator>

Address::Address(std::vector<DimAddress> addresses) : addresses(addresses) {}

std::vector<Address::prefix_type>
Address::prefixes() {

	std::vector<Address::prefix_type> partials = {{}};
	for(auto address : addresses) {
		std::vector<Address::prefix_type> temp;
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

Address::prefix_type
Address::exact() {
	Address::prefix_type out;
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
