#include <boost/test/unit_test.hpp>

#include "MediatedCube.h"

#include <cryptopp/hex.h>
#include <iostream>

BOOST_AUTO_TEST_SUITE(MediatedCubeTest)

BOOST_AUTO_TEST_CASE(OnePoint) 
{
	MediatedCube m;

	Address a({ DimAddress("00"), DimAddress("11")});
	m.add(a, 1);

	std::vector<Address> ones = {
		Address({ DimAddress("00"), DimAddress("11")}),
		Address({ DimAddress("00"), DimAddress("1")}),
		Address({ DimAddress("00"), DimAddress("")}),
		Address({ DimAddress("0"), DimAddress("11")}),
		Address({ DimAddress("0"), DimAddress("1")}),
		Address({ DimAddress("0"), DimAddress("")}),
		Address({ DimAddress(""), DimAddress("11")}),
		Address({ DimAddress(""), DimAddress("1")}),
		Address({ DimAddress(""), DimAddress("")})
	};
	for(auto address : ones)
		BOOST_CHECK_EQUAL(1, m.lookup(address));

	std::vector<Address> zeros = {
		Address({ DimAddress("10"), DimAddress("11")}),
	};

	for(auto address : zeros)
		BOOST_CHECK_EQUAL(0, m.lookup(address));
}

BOOST_AUTO_TEST_CASE(Aggregate) 
{
	MediatedCube m;

	m.add(Address({ DimAddress("0"), DimAddress("0")}), 1);
	m.add(Address({ DimAddress("0"), DimAddress("1")}), 1);

	BOOST_CHECK_EQUAL(2, m.lookup(Address({ DimAddress("0"), DimAddress("") })));
	BOOST_CHECK_EQUAL(2, m.lookup(Address({ DimAddress(""), DimAddress("") })));
}

BOOST_AUTO_TEST_CASE(MissedLookups) 
{
	MediatedCube m;

	std::vector<Address> addresses = {
		Address({ DimAddress("00"), DimAddress("11")}),
		Address({ DimAddress("00"), DimAddress("1")}),
		Address({ DimAddress("00"), DimAddress("")}),
		Address({ DimAddress("0"), DimAddress("11")}),
		Address({ DimAddress("0"), DimAddress("1")}),
		Address({ DimAddress("0"), DimAddress("")}),
		Address({ DimAddress(""), DimAddress("11")}),
		Address({ DimAddress(""), DimAddress("1")}),
		Address({ DimAddress(""), DimAddress("")})
	};
	
	for(auto a : addresses)
		BOOST_CHECK_EQUAL(0, m.lookup(a));

	auto summary = m.size_summary();
	BOOST_CHECK_EQUAL(0, std::get<0>(summary));
}

BOOST_AUTO_TEST_CASE(RepeatKeys) 
{
	MediatedCube m;

	std::vector<Address> addresses = {
		Address({ DimAddress("00"), DimAddress("11")}),
		Address({ DimAddress("00"), DimAddress("11")}),
	};

	for(auto a : addresses)
		m.add(a, 1);

	std::vector<Address> prefixes = {
		Address({ DimAddress("00"), DimAddress("11")}),
		Address({ DimAddress("0"), DimAddress("11")}),
		Address({ DimAddress(""), DimAddress("11")}),
		Address({ DimAddress("00"), DimAddress("1")}),
		Address({ DimAddress("0"), DimAddress("1")}),
		Address({ DimAddress(""), DimAddress("1")}),
		Address({ DimAddress("00"), DimAddress("")}),
		Address({ DimAddress("0"), DimAddress("")}),
		Address({ DimAddress(""), DimAddress("")}),
	};
	
	for(auto a : prefixes)
		BOOST_CHECK_EQUAL(2, m.lookup(a));
}

BOOST_AUTO_TEST_SUITE_END()
