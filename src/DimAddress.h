#pragma once

#include <string>
#include <vector>

class DimAddress {

public:
	typedef uint64_t address_type;

	DimAddress(std::string key);

	std::vector<address_type> prefixes();

	address_type exact();

	friend std::ostream &operator<<(std::ostream & o, DimAddress const& d);

private:
	std::string key;
};
