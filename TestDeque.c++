// ----------------------------
// projects/deque/TestDeque.c++
// Copyright (C) 2014
// Glenn P. Downing
// ----------------------------

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

/*
Google Test Libraries:
    % ls -al /usr/include/gtest/
    ...
    gtest.h
    ...

    % locate libgtest.a
    /usr/lib/libgtest.a

    % locate libpthread.a
    /usr/lib/x86_64-linux-gnu/libpthread.a
    /usr/lib32/libpthread.a

    % locate libgtest_main.a
    /usr/lib/libgtest_main.a

To compile the test:
    % g++-4.7 -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -Wall TestDeque.c++ -o TestDeque -lgtest -lgtest_main -lpthread 

To run the test:
    % valgrind TestDeque

To obtain coverage of the test:
    % gcov-4.7 -b TestDeque.c++
*/

// --------
// includes
// --------

#include <algorithm> // equal
#include <cstring>   // strcmp
#include <deque>     // deque
#include <sstream>   // ostringstream
#include <stdexcept> // invalid_argument
#include <string>    // ==

#include "gtest/gtest.h"

#include "Deque.h"

// ---------
// TestDeque
// ---------

// Documentation for Typed Tests: 
// https://code.google.com/p/googletest/wiki/AdvancedGuide#Typed_Tests

// Define a test that inherits from the google test base class.
template <typename D>
struct TestDeque : testing::Test {
  // --------
  // typedefs
  // --------

  typedef          D                  deque_type;
  typedef typename D::allocator_type  allocator_type;
  typedef typename D::value_type      value_type;
  typedef typename D::size_type       size_type;
  typedef typename D::difference_type difference_type;
  typedef typename D::pointer         pointer;
  typedef typename D::const_pointer   const_pointer;
  typedef typename D::reference       reference;
  typedef typename D::const_reference const_reference;};

// Specify the types of deques for which all of our tests will be run.
// Here we specify 4 deque types, so each test will get run 4 times.
typedef testing::Types< std::deque<int>,
                        std::deque<double>,
                        my_deque<int>,
                        my_deque<double> >
        my_types;

TYPED_TEST_CASE(TestDeque, my_types);

TYPED_TEST(TestDeque, Empty_1) {
  typedef typename TestFixture::deque_type      deque_type;
  typedef typename TestFixture::allocator_type  allocator_type;
  typedef typename TestFixture::value_type      value_type;
  typedef typename TestFixture::size_type       size_type;
  typedef typename TestFixture::difference_type difference_type;
  typedef typename TestFixture::pointer         pointer;
  typedef typename TestFixture::const_pointer   const_pointer;
  typedef typename TestFixture::reference       reference;
  typedef typename TestFixture::const_reference const_reference;

  deque_type x;
  const bool b = x.empty();
  ASSERT_TRUE(b);
}

TYPED_TEST(TestDeque, Empty_2) {
  typedef typename TestFixture::deque_type      deque_type;
  typedef typename TestFixture::allocator_type  allocator_type;
  typedef typename TestFixture::value_type      value_type;
  typedef typename TestFixture::size_type       size_type;
  typedef typename TestFixture::difference_type difference_type;
  typedef typename TestFixture::pointer         pointer;
  typedef typename TestFixture::const_pointer   const_pointer;
  typedef typename TestFixture::reference       reference;
  typedef typename TestFixture::const_reference const_reference;

  deque_type x(27);
  const bool b = x.empty();
  ASSERT_FALSE(b);
}

TYPED_TEST(TestDeque, Size_1) {
  typedef typename TestFixture::deque_type      deque_type;
  typedef typename TestFixture::allocator_type  allocator_type;
  typedef typename TestFixture::value_type      value_type;
  typedef typename TestFixture::size_type       size_type;
  typedef typename TestFixture::difference_type difference_type;
  typedef typename TestFixture::pointer         pointer;
  typedef typename TestFixture::const_pointer   const_pointer;
  typedef typename TestFixture::reference       reference;
  typedef typename TestFixture::const_reference const_reference;

  deque_type x;
  const size_type s = x.size();
  ASSERT_EQ(0, s);
}

TYPED_TEST(TestDeque, Size_2) {
  typedef typename TestFixture::deque_type      deque_type;
  typedef typename TestFixture::allocator_type  allocator_type;
  typedef typename TestFixture::value_type      value_type;
  typedef typename TestFixture::size_type       size_type;
  typedef typename TestFixture::difference_type difference_type;
  typedef typename TestFixture::pointer         pointer;
  typedef typename TestFixture::const_pointer   const_pointer;
  typedef typename TestFixture::reference       reference;
  typedef typename TestFixture::const_reference const_reference;

  deque_type x(32);
  const size_type s = x.size();
  ASSERT_EQ(32, s);
}

TYPED_TEST(TestDeque, Size_3) {
  typedef typename TestFixture::deque_type      deque_type;
  typedef typename TestFixture::allocator_type  allocator_type;
  typedef typename TestFixture::value_type      value_type;
  typedef typename TestFixture::size_type       size_type;
  typedef typename TestFixture::difference_type difference_type;
  typedef typename TestFixture::pointer         pointer;
  typedef typename TestFixture::const_pointer   const_pointer;
  typedef typename TestFixture::reference       reference;
  typedef typename TestFixture::const_reference const_reference;

  deque_type x;
  for (int i = 0; i < 30; ++i) {
    x.push_back(i);
    x.push_front(i);
  }
  const size_type s = x.size();
  ASSERT_EQ(60, s);
}

TYPED_TEST(TestDeque, Constructor_1) {
  typedef typename TestFixture::deque_type      deque_type;

  deque_type x(56);
  // TODO
}
