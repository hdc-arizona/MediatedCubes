#include <boost/test/unit_test.hpp>

#include "Hasher.h"


BOOST_AUTO_TEST_SUITE(HasherTest)

BOOST_AUTO_TEST_CASE(UpdateDoesNotCommuteWithConcat) 
{
	Hasher h;
	Hasher g;
	h.update(1);
	h.update(2);
	g.update(12);

	BOOST_CHECK(h.digest() != g.digest());	
}

BOOST_AUTO_TEST_CASE(CopyProducesIdentical)
{
	Hasher h;
	h.update(1);
	Hasher g = h;

	BOOST_CHECK(h.digest() == g.digest());

	h.update(2);
	g.update(2);

	BOOST_CHECK(h.digest() == g.digest());
}

BOOST_AUTO_TEST_CASE(DigestIsIdempotent)
{
	Hasher h;
	h.update(1);

	BOOST_CHECK(h.digest() == h.digest());
}

BOOST_AUTO_TEST_CASE(CopyProducesDisjoint)
{
	Hasher h;
	h.update(1);
	Hasher g = h;

	auto digest1 = h.digest();
	g.update(2);
	auto digest2 = h.digest();

	BOOST_CHECK(digest1 == digest2);
}

BOOST_AUTO_TEST_CASE(CopyProducesDisjointReverse)
{
	Hasher h;
	h.update(1);
	Hasher g = h;

	auto digest1 = g.digest();
	h.update(2);
	auto digest2 = g.digest();

	BOOST_CHECK(digest1 == digest2);
}

BOOST_AUTO_TEST_SUITE_END()
