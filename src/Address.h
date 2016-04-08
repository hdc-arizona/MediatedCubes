#pragma once

#include <vector>
#include <set>
#include <iterator>
#include <boost/functional/hash.hpp>

#include "DimAddress.h"

class Address {

public:
	typedef std::vector<uint64_t> prefix_type;

	Address(std::vector<DimAddress> addresses);

	std::vector<prefix_type> prefixes();
	prefix_type exact();

	friend std::ostream &operator<<(std::ostream & o, Address const& a);

private:

	std::vector<DimAddress> addresses;
};

namespace std {
	template<> struct hash<Address::prefix_type> {
		typedef Address::prefix_type argument_type;
		typedef size_t result_type;
		result_type operator()(argument_type const& a) const {
			return boost::hash_range(a.begin(), a.end());	
		}
	};
}

namespace std {
	template <typename T>
	std::ostream &operator<<(std::ostream & o, std::vector<T> const& v) {
		o << "Vector(";
		std::copy(v.begin(), v.end(), std::ostream_iterator<T>(o, ","));
		o << ")";
		return o;
	}
}

