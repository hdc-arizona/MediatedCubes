#pragma once

#include <string>
#include <vector>
#include <boost/functional/hash.hpp>

#include <cryptopp/sha.h>

class Hasher {

public:

	typedef CryptoPP::SHA256 hash_type;
	typedef std::vector<uint8_t> digest_type;

	Hasher() = default;
	Hasher(Hasher & other) = default;
	Hasher(Hasher const & other) = default;

	template <typename T>
	void update(T x);

	digest_type digest();
	std::string hexdigest();

private:
	hash_type hasher;
};

template <typename T>
void Hasher::update(T x) {
	hasher.Update(reinterpret_cast<uint8_t *>(&x), sizeof(T));
}

namespace std {
	template<> struct hash<std::vector<uint8_t>> {
		typedef std::vector<uint8_t> argument_type;
		typedef size_t result_type;
		result_type operator()(argument_type const& a) const {
			return boost::hash_range(a.begin(), a.end());	
		}
	};
}
