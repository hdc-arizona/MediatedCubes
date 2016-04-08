#include <boost/test/unit_test.hpp>

#include "Address.h"
#include "DimAddress.h"


BOOST_AUTO_TEST_SUITE(AddressTest)

BOOST_AUTO_TEST_CASE(FullPrefix) 
{
	DimAddress d("010");
	Address a({ d, d });
	std::vector<std::vector<std::string>> prefixes = 
		{ 
			{ "", "" },
			{ "", "0" },
			{ "", "01" },
			{ "", "010" },
			{ "0", "" },
			{ "0", "0" },
			{ "0", "01" },
			{ "0", "010" },
			{ "01", "" },
			{ "01", "0" },
			{ "01", "01" },
			{ "01", "010" },
			{ "010", "" },
			{ "010", "0" },
			{ "010", "01" },
			{ "010", "010" },
		};

	auto to_test = a.prefixes();
	
	std::sort(to_test.begin(), to_test.end());
	std::sort(prefixes.begin(), prefixes.end());

	BOOST_CHECK_EQUAL(prefixes, to_test);
}

BOOST_AUTO_TEST_CASE(EmptyPrefix) 
{
	DimAddress d("");
	std::vector<std::string> prefixes = { "" };

	BOOST_CHECK(prefixes == d.prefixes());
}

BOOST_AUTO_TEST_CASE(Exact) 
{
	DimAddress d("01");
	DimAddress e("010");
	Address a({ d, e });
	std::vector<std::string> exact = { "01", "010" };

	BOOST_CHECK(exact == a.exact());
}

BOOST_AUTO_TEST_SUITE_END()
