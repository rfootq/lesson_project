#define BOOST_TEST_MODULE lesson_project_test_module

#include "lib.h"

#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_SUITE( lesson_project_test_suite )

BOOST_AUTO_TEST_CASE( lesson_project_test_version )
{
    BOOST_CHECK(version() > 0);
}

BOOST_AUTO_TEST_SUITE_END()
