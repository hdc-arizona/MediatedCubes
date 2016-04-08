#include "Hasher.h"

std::vector<uint8_t> Hasher::digest() {
	uint8_t bytes[ hash_type::DIGESTSIZE ];
	auto copy = hasher;
	copy.Final(bytes);
	return digest_type(bytes, bytes + hash_type::DIGESTSIZE);
}

uint8_t to_hex(uint8_t x) {
	assert(x < 16);
	return (x < 10) ? x + '0' : x - 10 + 'A' ;
}

std::string Hasher::hexdigest() {
	std::vector<uint8_t> c;
	for(auto x : digest()) {
		c.push_back(to_hex(x / 16));
		c.push_back(to_hex(x % 16));
	}
	return std::string(c.begin(), c.end());
}
