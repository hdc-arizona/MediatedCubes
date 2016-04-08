#include <boost/test/unit_test.hpp>

#include "Address.h"
#include "DimAddress.h"

BOOST_AUTO_TEST_SUITE(AddressTest)

BOOST_AUTO_TEST_CASE(FullPrefix) 
{
	DimAddress d("010");
	Address a({ d, d });

	auto p = a.prefixes();
	BOOST_CHECK_EQUAL(16, p.size());
}

BOOST_AUTO_TEST_SUITE_END()
