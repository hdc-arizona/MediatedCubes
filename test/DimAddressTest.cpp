#include <boost/test/unit_test.hpp>

#include "DimAddress.h"


BOOST_AUTO_TEST_SUITE(DimAddressTest)

BOOST_AUTO_TEST_CASE(FullPrefixTest) 
{
	DimAddress d("010");
	std::vector<std::string> prefixes = { "", "0", "01", "010" };

	BOOST_CHECK(prefixes == d.prefixes());
}

BOOST_AUTO_TEST_CASE(EmptyPrefixTest) 
{
	DimAddress d("");
	std::vector<std::string> prefixes = { "" };

	BOOST_CHECK(prefixes == d.prefixes());
}

BOOST_AUTO_TEST_SUITE_END()
