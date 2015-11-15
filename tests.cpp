#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE BIG_NUMBERS_TEST

#include <boost/test/unit_test.hpp>
#include "BigNumbers.h"

BigNumbers bg_test;
vector<long> * answer = bg_test.get_result();

BOOST_AUTO_TEST_CASE(ADDITION_TEST) {
    // Addition test
    bg_test = BigNumbers("1111111111111",
                         "2222222222222", '+');
    bg_test.process();

    BOOST_CHECK_EQUAL((*answer)[0], 333333333);
    BOOST_CHECK_EQUAL((*answer)[1], 3333);
}

BOOST_AUTO_TEST_CASE(OVERFLOW_TEST){
    // Overflow test
    bg_test = BigNumbers("999999999",
                         "999999999", '+');
    bg_test.process();

    BOOST_CHECK_EQUAL((*answer)[0], 999999998);
    BOOST_CHECK_EQUAL((*answer)[1], 1);
}

BOOST_AUTO_TEST_CASE(SUBTRACTION_TEST){
    // Subtraction test
    bg_test = BigNumbers("999999998",
                         "999999999", '-');
    bg_test.process();

    BOOST_CHECK_EQUAL((*answer)[0], -1);


    bg_test = BigNumbers("700000000111111111",
                         "200000000222222222", '-');
    bg_test.process();
    BOOST_CHECK_EQUAL((*answer)[0], 888888889);
    BOOST_CHECK_EQUAL((*answer)[1], 499999999);
}

BOOST_AUTO_TEST_CASE(OTHER_TESTS) {
    bg_test = BigNumbers("-100000000111111111",
                         "-222222222", '-');
    bg_test.process();

    BOOST_CHECK_EQUAL((*answer)[0], 111111111);
    BOOST_CHECK_EQUAL((*answer)[1], -100000000);


    bg_test = BigNumbers("-100000000",
                         "50000000", '-');
    bg_test.process();

    BOOST_CHECK_EQUAL((*answer)[0], -150000000);
}