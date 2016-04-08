#pragma once

#include <string>
#include <vector>

class DimAddress {

public:
	DimAddress(std::string key);

	std::vector<std::string> prefixes();

	std::string exact();

	friend std::ostream &operator<<(std::ostream & o, DimAddress const& d);

private:
	std::string key;
};
