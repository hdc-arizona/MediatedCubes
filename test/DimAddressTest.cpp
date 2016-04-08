#include <boost/test/unit_test.hpp>

#include "DimAddress.h"

template <typename T>
void CHECK_NOT_EQUAL(T a, T b) {
	BOOST_CHECK_PREDICATE(std::not_equal_to<T>(), (a)(b));
}

BOOST_AUTO_TEST_SUITE(DimAddressTest)

BOOST_AUTO_TEST_CASE(FullPrefixTest) 
{
	DimAddress d("010");

	BOOST_CHECK(4 == d.prefixes().size());
}

BOOST_AUTO_TEST_CASE(NoCollisionOnZeroPrefix)
{
	CHECK_NOT_EQUAL(DimAddress("011").exact(), DimAddress("010").exact());
}

BOOST_AUTO_TEST_SUITE_END()
