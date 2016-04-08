#include <boost/test/unit_test.hpp>

#include "DimAddress.h"


BOOST_AUTO_TEST_SUITE(DimAddressTest)

BOOST_AUTO_TEST_CASE(FullPrefixTest) 
{
	DimAddress d("010");

	BOOST_CHECK(4 == d.prefixes().size());
}

BOOST_AUTO_TEST_SUITE_END()
