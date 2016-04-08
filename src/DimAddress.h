#pragma once

#include <string>
#include <vector>

class DimAddress {

public:
	DimAddress(std::string key);

	std::vector<uint64_t> prefixes();

	uint64_t exact();

	friend std::ostream &operator<<(std::ostream & o, DimAddress const& d);

private:
	std::string key;
};
