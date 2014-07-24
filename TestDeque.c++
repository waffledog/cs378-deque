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

/*----------------------------------------------------------------------------*\
    DEQUE CLASS TESTS
\*----------------------------------------------------------------------------*/

TYPED_TEST(TestDeque, EqualEqual_1) {
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
  deque_type y;
  ASSERT_EQ(x, y);
}

TYPED_TEST(TestDeque, EqualEqual_2) {
  typedef typename TestFixture::deque_type      deque_type;
  typedef typename TestFixture::allocator_type  allocator_type;
  typedef typename TestFixture::value_type      value_type;
  typedef typename TestFixture::size_type       size_type;
  typedef typename TestFixture::difference_type difference_type;
  typedef typename TestFixture::pointer         pointer;
  typedef typename TestFixture::const_pointer   const_pointer;
  typedef typename TestFixture::reference       reference;
  typedef typename TestFixture::const_reference const_reference;

  deque_type x(40);
  deque_type y(40);
  const deque_type z(x);
  for (int i = 0; i < 40; ++i) {
    x[i] = 33;
    y[i] = 33;
  }

  ASSERT_EQ(x, y);
  ASSERT_EQ(x, z);
}

TYPED_TEST(TestDeque, Clear_1) {
  typedef typename TestFixture::deque_type      deque_type;
  typedef typename TestFixture::allocator_type  allocator_type;
  typedef typename TestFixture::value_type      value_type;
  typedef typename TestFixture::size_type       size_type;
  typedef typename TestFixture::difference_type difference_type;
  typedef typename TestFixture::pointer         pointer;
  typedef typename TestFixture::const_pointer   const_pointer;
  typedef typename TestFixture::reference       reference;
  typedef typename TestFixture::const_reference const_reference;

  deque_type x(40, 5);
  ASSERT_EQ(x.size(), 40);
  x.clear();
  ASSERT_TRUE(x.empty());
}

TYPED_TEST(TestDeque, Clear_2) {
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
  ASSERT_TRUE(x.empty());
  x.clear();
  ASSERT_TRUE(x.empty());
}

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

TYPED_TEST(TestDeque, PushBack_1) {
  typedef typename TestFixture::deque_type      deque_type;
  typedef typename TestFixture::allocator_type  allocator_type;
  typedef typename TestFixture::value_type      value_type;
  typedef typename TestFixture::size_type       size_type;
  typedef typename TestFixture::difference_type difference_type;
  typedef typename TestFixture::pointer         pointer;
  typedef typename TestFixture::const_pointer   const_pointer;
  typedef typename TestFixture::reference       reference;
  typedef typename TestFixture::const_reference const_reference;

  deque_type x(10);
  for (int i = 10; i < 15; ++i) {
    x.push_back(i);
    ASSERT_EQ(x[i], i);
  }
  const size_type s = x.size();
  ASSERT_EQ(15, s);
}

TYPED_TEST(TestDeque, PushBack_2) {
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
  ASSERT_TRUE(x.empty());
  for (int i = 0; i < 1000; ++i) {
    x.push_back(i);
    ASSERT_EQ(x[i], i);
  }
  ASSERT_EQ(1000, x.size());
}

TYPED_TEST(TestDeque, PushBack_3) {
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
  ASSERT_TRUE(x.empty());
  for (int i = 0; i < 500; ++i) {
    x.push_back(i);
    ASSERT_EQ(x[i], i);
  }
  ASSERT_EQ(500, x.size());
  x.clear();
  ASSERT_TRUE(x.empty());
  for (int i = 0; i < 500; ++i) {
    x.push_back(i);
    ASSERT_EQ(x[i], i);
  }
  ASSERT_EQ(500, x.size());
}

TYPED_TEST(TestDeque, Constructor_1) {
  typedef typename TestFixture::deque_type      deque_type;
  deque_type x;
  ASSERT_EQ(x.size(), 0);
}

TYPED_TEST(TestDeque, Constructor_2) {
  typedef typename TestFixture::deque_type      deque_type;
  deque_type x(56);
  ASSERT_EQ(x.size(), 56);
}

TYPED_TEST(TestDeque, Copy_Constructor_1) {
  typedef typename TestFixture::deque_type      deque_type;

  deque_type x(100);
  for (int i = 0; i < 100; ++i) {
    x[i] = i;
  }
  deque_type y(x);
  ASSERT_EQ(x, y);
  ASSERT_NE(&x, &y);
}

TYPED_TEST(TestDeque, Copy_Constructor_2) {
  typedef typename TestFixture::deque_type      deque_type;

  deque_type x;
  deque_type y(x);
  ASSERT_EQ(x, y);
  ASSERT_NE(&x, &y);
}

TYPED_TEST(TestDeque, CopyAssign_1) {
  typedef typename TestFixture::deque_type      deque_type;
  typedef typename TestFixture::value_type      value_type;

  const value_type& v1 = 1;
  const value_type& v2 = 2;
  const deque_type x(10, v1);
  deque_type y(20, v2);
  ASSERT_EQ(x.size(), 10);
  ASSERT_EQ(y.size(), 20);
  ASSERT_NE(x, y);
  y = x;
  ASSERT_EQ(x.size(), 10);
  ASSERT_EQ(y.size(), 10);
  ASSERT_EQ(x, y);
  ASSERT_EQ(x[0], 1);
}

TYPED_TEST(TestDeque, CopyAssign_2) {
  typedef typename TestFixture::deque_type      deque_type;
  typedef typename TestFixture::value_type      value_type;

  const value_type& v1 = 1;
  const value_type& v2 = 2;
  deque_type x(10, v1);
  const deque_type y(20, v2);
  ASSERT_EQ(x.size(), 10);
  ASSERT_EQ(y.size(), 20);
  ASSERT_NE(x, y);
  x = y;
  ASSERT_EQ(x.size(), 20);
  ASSERT_EQ(y.size(), 20);
  ASSERT_EQ(x, y);
  ASSERT_EQ(x[0], 2);
}

TYPED_TEST(TestDeque, CopyAssign_3) {
  typedef typename TestFixture::deque_type      deque_type;
  typedef typename TestFixture::value_type      value_type;

  const value_type& v1 = 1;
  const value_type& v2 = 2;
  deque_type x(15, v1);
  const deque_type y(16, v2);
  ASSERT_EQ(x.size(), 15);
  ASSERT_EQ(y.size(), 16);
  ASSERT_NE(x, y);
  x = y;
  ASSERT_EQ(x.size(), 16);
  ASSERT_EQ(y.size(), 16);
  ASSERT_EQ(x, y);
  ASSERT_EQ(x[0], 2);
}

TYPED_TEST(TestDeque, Subscript_1) {
  typedef typename TestFixture::deque_type      deque_type;
  typedef typename TestFixture::allocator_type  allocator_type;
  typedef typename TestFixture::value_type      value_type;
  typedef typename TestFixture::size_type       size_type;
  typedef typename TestFixture::difference_type difference_type;
  typedef typename TestFixture::pointer         pointer;
  typedef typename TestFixture::const_pointer   const_pointer;
  typedef typename TestFixture::reference       reference;
  typedef typename TestFixture::const_reference const_reference;

  deque_type x(3);
  for(int i = 0; i < 3; i++) {
    ASSERT_EQ(x[i], 0);
  }
}

TYPED_TEST(TestDeque, Subscript_2) {
  typedef typename TestFixture::deque_type      deque_type;
  typedef typename TestFixture::allocator_type  allocator_type;
  typedef typename TestFixture::value_type      value_type;
  typedef typename TestFixture::size_type       size_type;
  typedef typename TestFixture::difference_type difference_type;
  typedef typename TestFixture::pointer         pointer;
  typedef typename TestFixture::const_pointer   const_pointer;
  typedef typename TestFixture::reference       reference;
  typedef typename TestFixture::const_reference const_reference;

  deque_type x(1000);
  ASSERT_EQ(x[1], 0);
  ASSERT_EQ(x[999], 0);

  for(int j = 0; j < 1000; j++) {
    x[j] = 5;
    ASSERT_EQ(x[j], 5);
  }
}

TYPED_TEST(TestDeque, At_1) {
  typedef typename TestFixture::deque_type      deque_type;
  typedef typename TestFixture::allocator_type  allocator_type;
  typedef typename TestFixture::value_type      value_type;
  typedef typename TestFixture::size_type       size_type;
  typedef typename TestFixture::difference_type difference_type;
  typedef typename TestFixture::pointer         pointer;
  typedef typename TestFixture::const_pointer   const_pointer;
  typedef typename TestFixture::reference       reference;
  typedef typename TestFixture::const_reference const_reference;

  deque_type x(15);
  for (int i = 0; i < 15; ++i) {
    x.at(i) = i;
  }
  for (int i = 0; i < 15; ++i) {
    ASSERT_EQ(x[i], i);
  }
}

TYPED_TEST(TestDeque, At_2) {
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
  try {
    x.at(15);
    ASSERT_TRUE(false);
  }
  catch(const std::out_of_range&) {}
}

TYPED_TEST(TestDeque, Const_At_1) {
  typedef typename TestFixture::deque_type      deque_type;
  typedef typename TestFixture::allocator_type  allocator_type;
  typedef typename TestFixture::value_type      value_type;
  typedef typename TestFixture::size_type       size_type;
  typedef typename TestFixture::difference_type difference_type;
  typedef typename TestFixture::pointer         pointer;
  typedef typename TestFixture::const_pointer   const_pointer;
  typedef typename TestFixture::reference       reference;
  typedef typename TestFixture::const_reference const_reference;

  const deque_type x;
  try {
    x.at(15);
    ASSERT_TRUE(false);
  }
  catch(const std::out_of_range&) {}
}

TYPED_TEST(TestDeque, Back_1) {
  typedef typename TestFixture::deque_type      deque_type;
  typedef typename TestFixture::allocator_type  allocator_type;
  typedef typename TestFixture::value_type      value_type;
  typedef typename TestFixture::size_type       size_type;
  typedef typename TestFixture::difference_type difference_type;
  typedef typename TestFixture::pointer         pointer;
  typedef typename TestFixture::const_pointer   const_pointer;
  typedef typename TestFixture::reference       reference;
  typedef typename TestFixture::const_reference const_reference;

  deque_type x(30);
  x[29] = 99;
  ASSERT_EQ(x.back(), 99);

  typename deque_type::iterator i = x.end();
  i -= 1;
  ASSERT_EQ(x.back(), *i);
  ASSERT_EQ(&(x.back()), &(*i));
}

TYPED_TEST(TestDeque, Back_2) {
  typedef typename TestFixture::deque_type      deque_type;
  typedef typename TestFixture::allocator_type  allocator_type;
  typedef typename TestFixture::value_type      value_type;
  typedef typename TestFixture::size_type       size_type;
  typedef typename TestFixture::difference_type difference_type;
  typedef typename TestFixture::pointer         pointer;
  typedef typename TestFixture::const_pointer   const_pointer;
  typedef typename TestFixture::reference       reference;
  typedef typename TestFixture::const_reference const_reference;

  deque_type x(30);
  x[29] = 99;

  reference b = x.back();
  ASSERT_EQ(b, 99);

  b += 1;
  ASSERT_EQ(x.back(), 100);
}

TYPED_TEST(TestDeque, Const_Back_1) {
  typedef typename TestFixture::deque_type      deque_type;
  typedef typename TestFixture::allocator_type  allocator_type;
  typedef typename TestFixture::value_type      value_type;
  typedef typename TestFixture::size_type       size_type;
  typedef typename TestFixture::difference_type difference_type;
  typedef typename TestFixture::pointer         pointer;
  typedef typename TestFixture::const_pointer   const_pointer;
  typedef typename TestFixture::reference       reference;
  typedef typename TestFixture::const_reference const_reference;

  deque_type x(30);
  x[29] = 99;
  const deque_type y = x;

  const_reference b = y.back();
  ASSERT_EQ(b, 99);
  ASSERT_EQ(&b, &y[29]);
}

// TODO: Test Deque clear() 

// TODO: Test Deque end() 

// TODO: Test Deque const_iterator end() 

TYPED_TEST(TestDeque, Front_1) {
  typedef typename TestFixture::deque_type      deque_type;
  typedef typename TestFixture::reference       reference;
  typedef typename TestFixture::const_reference const_reference;
  
  deque_type x(5, 7);
  ASSERT_EQ(x.front(), 7);
  ASSERT_EQ(&x.front(), &x[0]);
}

TYPED_TEST(TestDeque, Front_2) {
  typedef typename TestFixture::deque_type      deque_type;
  typedef typename TestFixture::reference       reference;
  typedef typename TestFixture::const_reference const_reference;
  
  deque_type x(15, 1);
  reference r = x.front();
  ASSERT_EQ(r, 1);
  r = 20;
  ASSERT_EQ(x.front(), 20);
}

TYPED_TEST(TestDeque, Front_3) {
  typedef typename TestFixture::deque_type      deque_type;
  typedef typename TestFixture::reference       reference;
  typedef typename TestFixture::const_reference const_reference;
  
  deque_type x(15, 1);
  x[0] = 20;
  ASSERT_EQ(x.front(), 20);
  x.pop_back();
  x.pop_back();
  x.push_back(3);
  ASSERT_EQ(x.front(), 20);
  x.pop_front();
  ASSERT_EQ(x.front(), 1);
}

TYPED_TEST(TestDeque, Front_4) {
  typedef typename TestFixture::deque_type      deque_type;
  typedef typename TestFixture::reference       reference;
  typedef typename TestFixture::const_reference const_reference;
  
  const deque_type x(15, 1);
  const_reference cr = x.front();
  ASSERT_EQ(cr, 1);
}

TYPED_TEST(TestDeque, Erase_1) {
  typedef typename TestFixture::deque_type      deque_type;
  typedef typename TestFixture::allocator_type  allocator_type;
  typedef typename TestFixture::value_type      value_type;
  typedef typename TestFixture::size_type       size_type;
  typedef typename TestFixture::difference_type difference_type;
  typedef typename TestFixture::pointer         pointer;
  typedef typename TestFixture::const_pointer   const_pointer;
  typedef typename TestFixture::reference       reference;
  typedef typename TestFixture::const_reference const_reference;

  deque_type x(10);
  for (int i = 0; i < 10; ++i) {
    x[i] = i;
  }
  ASSERT_EQ(x.size(), 10);
  // 0 1 2 3 4 5 6 7 8 9

  typename deque_type::iterator b = x.begin();
  x.erase(b + 3);
  // 0 1 2 4 5 6 7 8 9
  ASSERT_EQ(x.size(), 9);
  ASSERT_EQ(x[3], 4);

  x.erase(b);
  // 1 2 4 5 6 7 8 9
  ASSERT_EQ(x.size(), 8);
  ASSERT_EQ(x[3], 5);
}

TYPED_TEST(TestDeque, Erase_2) {
  typedef typename TestFixture::deque_type      deque_type;
  typedef typename TestFixture::allocator_type  allocator_type;
  typedef typename TestFixture::value_type      value_type;
  typedef typename TestFixture::size_type       size_type;
  typedef typename TestFixture::difference_type difference_type;
  typedef typename TestFixture::pointer         pointer;
  typedef typename TestFixture::const_pointer   const_pointer;
  typedef typename TestFixture::reference       reference;
  typedef typename TestFixture::const_reference const_reference;

  deque_type x(100);
  for (int i = 0; i < 100; ++i) {
    x[i] = i;
  }
  ASSERT_EQ(x.size(), 100);

  typename deque_type::iterator b = x.begin();
  x.erase(b + 87);
  ASSERT_EQ(x.size(), 99);
  ASSERT_EQ(x[87], 88);

  for (int i = 0; i < 99; ++i) {
    x.erase(b);
  }
  ASSERT_TRUE(x.empty());
}

TYPED_TEST(TestDeque, Pop_Back_1) {
  typedef typename TestFixture::deque_type      deque_type;

  deque_type x(369);
  for (int i = 0; i < 369; ++i) {
    x[i] = i;
  }
  ASSERT_EQ(x.size(), 369);

  for (int i = 0; i < 369; ++i) {
    x.pop_back();
  }
  ASSERT_TRUE(x.empty());
}

TYPED_TEST(TestDeque, Pop_Back_2) {
  typedef typename TestFixture::deque_type      deque_type;

  deque_type x;
  ASSERT_TRUE(x.empty());
  for (int i = 0; i < 500; ++i) {
    x.push_front(1);
  }
  ASSERT_EQ(x.size(), 500);
  for (int i = 0; i < 500; ++i) {
    x.pop_back();
  }
  ASSERT_TRUE(x.empty());
}

TYPED_TEST(TestDeque, Pop_Front_1) {
  typedef typename TestFixture::deque_type      deque_type;

  deque_type x(1);
  ASSERT_EQ(x.size(), 1);
  x.pop_front();
  ASSERT_TRUE(x.empty());
}

TYPED_TEST(TestDeque, Pop_Front_2) {
  typedef typename TestFixture::deque_type      deque_type;

  deque_type x(500);
  ASSERT_EQ(x.size(), 500);
  for (int i = 0; i < 500; ++i) {
    x.pop_back();
  }
  ASSERT_TRUE(x.empty());
}

TYPED_TEST(TestDeque, Pop_Front_3) {
  typedef typename TestFixture::deque_type      deque_type;

  deque_type x(1, 3);
  ASSERT_EQ(x.size(), 1);
  x.pop_front();
  ASSERT_TRUE(x.empty());
  x.push_back(5);
  ASSERT_EQ(x.size(), 1);
  ASSERT_EQ(x[0], 5);
}

TYPED_TEST(TestDeque, Swap_1) {
  typedef typename TestFixture::deque_type      deque_type;

  deque_type x(20, 1);
  deque_type y(35, 2);
  const deque_type x_copy(x);
  const deque_type y_copy(y);

  x.swap(y);
  ASSERT_EQ(x.size(), 35);
  ASSERT_EQ(x_copy.size(), 20);
  ASSERT_EQ(y.size(), 20);
  ASSERT_EQ(y_copy.size(), 35);


  for(int i = 0; i < 35; ++i) {
    ASSERT_EQ(x[i], y_copy[i]);
  }
  for(int j = 0; j < 20; ++j) {
    ASSERT_EQ(y[j], x_copy[j]);
  }

  for(int z = 0; z < y_copy.size(); ++z) {
    cout << "i: " << z << " val: " << y_copy[z]  << " x[i]: " << x[z] << endl ;
  }

  // ASSERT_EQ(x, y_copy);
}

TYPED_TEST(TestDeque, Swap_2) {
  typedef typename TestFixture::deque_type      deque_type;

  deque_type x;
  deque_type y(35, 2);
  const deque_type x_copy(x);
  ASSERT_EQ(x.size(), 0);
  const deque_type y_copy(y);

  x.swap(y);

  // ASSERT_EQ(y, x_copy);
  // ASSERT_EQ(x, y_copy);
}

TYPED_TEST(TestDeque, Swap_3) {
  typedef typename TestFixture::deque_type      deque_type;

  deque_type x;
  deque_type y;
  const deque_type x_copy(x);
  const deque_type y_copy(y);

  x.swap(y);

  ASSERT_EQ(y, x_copy);
  ASSERT_EQ(x, y_copy);
}

/*----------------------------------------------------------------------------*\
    ITERATOR CLASS TESTS
\*----------------------------------------------------------------------------*/

TYPED_TEST(TestDeque, Iterator_EqualEqual_1) {
  typedef typename TestFixture::deque_type      deque_type;
  typedef typename TestFixture::allocator_type  allocator_type;
  typedef typename TestFixture::value_type      value_type;
  typedef typename TestFixture::size_type       size_type;
  typedef typename TestFixture::difference_type difference_type;
  typedef typename TestFixture::pointer         pointer;
  typedef typename TestFixture::const_pointer   const_pointer;
  typedef typename TestFixture::reference       reference;
  typedef typename TestFixture::const_reference const_reference;

  deque_type x(10);

  typename deque_type::iterator b1 = x.begin();
  typename deque_type::iterator b2 = x.begin();

  ASSERT_TRUE(b1 == b2);
  b1 += 9;
  b2 += 5;
  b2 += 4;
  ASSERT_TRUE(b1 == b2);
}

TYPED_TEST(TestDeque, Iterator_NotEqual_1) {
  typedef typename TestFixture::deque_type      deque_type;
  typedef typename TestFixture::allocator_type  allocator_type;
  typedef typename TestFixture::value_type      value_type;
  typedef typename TestFixture::size_type       size_type;
  typedef typename TestFixture::difference_type difference_type;
  typedef typename TestFixture::pointer         pointer;
  typedef typename TestFixture::const_pointer   const_pointer;
  typedef typename TestFixture::reference       reference;
  typedef typename TestFixture::const_reference const_reference;

  deque_type x(10);
  deque_type y(10);

  typename deque_type::iterator b1 = x.begin();
  typename deque_type::iterator b2 = y.begin();

  ASSERT_TRUE(b1 != b2);
}

TYPED_TEST(TestDeque, Iterator_NotEqual_2) {
  typedef typename TestFixture::deque_type      deque_type;
  typedef typename TestFixture::allocator_type  allocator_type;
  typedef typename TestFixture::value_type      value_type;
  typedef typename TestFixture::size_type       size_type;
  typedef typename TestFixture::difference_type difference_type;
  typedef typename TestFixture::pointer         pointer;
  typedef typename TestFixture::const_pointer   const_pointer;
  typedef typename TestFixture::reference       reference;
  typedef typename TestFixture::const_reference const_reference;

  deque_type x(300);
  int count = 0;
  typename deque_type::iterator b = x.begin();
  typename deque_type::iterator e = x.end();

  while (b != e) {
    ++count;
    ++b;
  }

  ASSERT_EQ(count, 300);
}

TYPED_TEST(TestDeque, Iterator_Dereference_1) {
  typedef typename TestFixture::deque_type      deque_type;
  typedef typename TestFixture::allocator_type  allocator_type;
  typedef typename TestFixture::value_type      value_type;
  typedef typename TestFixture::size_type       size_type;
  typedef typename TestFixture::difference_type difference_type;
  typedef typename TestFixture::pointer         pointer;
  typedef typename TestFixture::const_pointer   const_pointer;
  typedef typename TestFixture::reference       reference;
  typedef typename TestFixture::const_reference const_reference;

  deque_type x(20);
  typename deque_type::iterator p = x.begin();
  x[0] = 5;
  ASSERT_EQ(*p, 5);
  p++;
  ASSERT_EQ(*p, 0);
  p--;
  ASSERT_EQ(*p, 5);
}

// Note: This is a non-typed test
TEST(TestMyDeque, Iterator_Arrow_1) {

  struct dummy {
    int x;
    int y;
    dummy() : x(1), y(2) {}
  };

  my_deque<dummy> x(10);
  typename my_deque<dummy>::iterator b = x.begin();
   
  for (int i = 0; i < 10; ++i) {
    ASSERT_EQ(b->x, 1); 
    ASSERT_EQ(b->y, 2); 
    ++b;
  }
}

TYPED_TEST(TestDeque, Iterator_PrePlusPlus_1) {
  typedef typename TestFixture::deque_type      deque_type;
  typedef typename TestFixture::allocator_type  allocator_type;
  typedef typename TestFixture::value_type      value_type;
  typedef typename TestFixture::size_type       size_type;
  typedef typename TestFixture::difference_type difference_type;
  typedef typename TestFixture::pointer         pointer;
  typedef typename TestFixture::const_pointer   const_pointer;
  typedef typename TestFixture::reference       reference;
  typedef typename TestFixture::const_reference const_reference;

  deque_type x(100);
  for (int i = 0; i < 100; ++i) {
    x[i] = i;
  }
  typename deque_type::iterator p = x.begin();

  for (int i = 0; i < 100; ++i) {
    ASSERT_EQ(*p, i);
    ++p;
  }
}

TYPED_TEST(TestDeque, Iterator_PostPlusPlus_1) {
  typedef typename TestFixture::deque_type      deque_type;
  typedef typename TestFixture::allocator_type  allocator_type;
  typedef typename TestFixture::value_type      value_type;
  typedef typename TestFixture::size_type       size_type;
  typedef typename TestFixture::difference_type difference_type;
  typedef typename TestFixture::pointer         pointer;
  typedef typename TestFixture::const_pointer   const_pointer;
  typedef typename TestFixture::reference       reference;
  typedef typename TestFixture::const_reference const_reference;

  deque_type x(100);
  for (int i = 0; i < 100; ++i) {
    x[i] = i;
  }
  typename deque_type::iterator p = x.begin();

  for (int i = 0; i < 100; ++i) {
    ASSERT_EQ(*p, i);
    value_type temp = *(p++);
    ASSERT_EQ(temp, i);
  }
}

TYPED_TEST(TestDeque, Iterator_PreMinusMinus_1) {
  typedef typename TestFixture::deque_type      deque_type;
  typedef typename TestFixture::allocator_type  allocator_type;
  typedef typename TestFixture::value_type      value_type;
  typedef typename TestFixture::size_type       size_type;
  typedef typename TestFixture::difference_type difference_type;
  typedef typename TestFixture::pointer         pointer;
  typedef typename TestFixture::const_pointer   const_pointer;
  typedef typename TestFixture::reference       reference;
  typedef typename TestFixture::const_reference const_reference;

  deque_type x(100);
  for (int i = 0; i < 100; ++i) {
    x[i] = i;
  }
  typename deque_type::iterator p = x.begin();
  p += 99;

  for (int i = 0; i < 100; ++i) {
    ASSERT_EQ(*p, 99 - i);
    --p;
  }
}

TYPED_TEST(TestDeque, Iterator_PostMinusMinus_1) {
  typedef typename TestFixture::deque_type      deque_type;
  typedef typename TestFixture::allocator_type  allocator_type;
  typedef typename TestFixture::value_type      value_type;
  typedef typename TestFixture::size_type       size_type;
  typedef typename TestFixture::difference_type difference_type;
  typedef typename TestFixture::pointer         pointer;
  typedef typename TestFixture::const_pointer   const_pointer;
  typedef typename TestFixture::reference       reference;
  typedef typename TestFixture::const_reference const_reference;

  deque_type x(100);
  for (int i = 0; i < 100; ++i) {
    x[i] = i;
  }
  typename deque_type::iterator p = x.begin();
  p += 99;

  for (int i = 0; i < 100; ++i) {
    ASSERT_EQ(*p, 99 - i);
    value_type temp = *(p--);
    ASSERT_EQ(temp, 99 - i);
  }
}

TYPED_TEST(TestDeque, Iterator_PlusEq_1) {
  typedef typename TestFixture::deque_type      deque_type;
  typedef typename TestFixture::allocator_type  allocator_type;
  typedef typename TestFixture::value_type      value_type;
  typedef typename TestFixture::size_type       size_type;
  typedef typename TestFixture::difference_type difference_type;
  typedef typename TestFixture::pointer         pointer;
  typedef typename TestFixture::const_pointer   const_pointer;
  typedef typename TestFixture::reference       reference;
  typedef typename TestFixture::const_reference const_reference;

  deque_type x(100);
  for (int i = 0; i < 100; ++i) {
    x[i] = i;
  }
  typename deque_type::iterator i = x.begin();
  ASSERT_EQ(*i, 0);
  i += 10;
  ASSERT_EQ(*i, 10);
  i += 33;
  ASSERT_EQ(*i, 43);
  i += 27;
  ASSERT_EQ(*i, 70);
  i += 11;
  ASSERT_EQ(*i, 81);
  i += 18;
  ASSERT_EQ(*i, 99);
}


TYPED_TEST(TestDeque, Iterator_MinusEq_1) {
  typedef typename TestFixture::deque_type      deque_type;
  typedef typename TestFixture::allocator_type  allocator_type;
  typedef typename TestFixture::value_type      value_type;
  typedef typename TestFixture::size_type       size_type;
  typedef typename TestFixture::difference_type difference_type;
  typedef typename TestFixture::pointer         pointer;
  typedef typename TestFixture::const_pointer   const_pointer;
  typedef typename TestFixture::reference       reference;
  typedef typename TestFixture::const_reference const_reference;

  deque_type x(100);
  for (int i = 0; i < 100; ++i) {
    x[i] = i;
  }
  typename deque_type::iterator i = x.begin();
  i += 99;
  ASSERT_EQ(*i, 99);
  i -= 10;
  ASSERT_EQ(*i, 89);
  i -= 9;
  ASSERT_EQ(*i, 80);
  i -= 45;
  ASSERT_EQ(*i, 35);
  i -= 35;
  ASSERT_EQ(*i, 0);
}

/*----------------------------------------------------------------------------*\
    CONST_ITERATOR CLASS TESTS
\*----------------------------------------------------------------------------*/

TYPED_TEST(TestDeque, Const_Iterator_EqualEqual_1) {
  typedef typename TestFixture::deque_type      deque_type;
  typedef typename TestFixture::allocator_type  allocator_type;
  typedef typename TestFixture::value_type      value_type;
  typedef typename TestFixture::size_type       size_type;
  typedef typename TestFixture::difference_type difference_type;
  typedef typename TestFixture::pointer         pointer;
  typedef typename TestFixture::const_pointer   const_pointer;
  typedef typename TestFixture::reference       reference;
  typedef typename TestFixture::const_reference const_reference;

  const deque_type x(10);

  typename deque_type::const_iterator b1 = x.begin();
  typename deque_type::const_iterator b2 = x.begin();

  ASSERT_TRUE(b1 == b2);
  b1 += 9;
  b2 += 5;
  b2 += 4;
  ASSERT_TRUE(b1 == b2);
}

TYPED_TEST(TestDeque, Const_Iterator_NotEqual_1) {
  typedef typename TestFixture::deque_type      deque_type;
  typedef typename TestFixture::allocator_type  allocator_type;
  typedef typename TestFixture::value_type      value_type;
  typedef typename TestFixture::size_type       size_type;
  typedef typename TestFixture::difference_type difference_type;
  typedef typename TestFixture::pointer         pointer;
  typedef typename TestFixture::const_pointer   const_pointer;
  typedef typename TestFixture::reference       reference;
  typedef typename TestFixture::const_reference const_reference;

  const deque_type x(10);
  const deque_type y(10);

  typename deque_type::const_iterator b1 = x.begin();
  typename deque_type::const_iterator b2 = y.begin();

  ASSERT_TRUE(b1 != b2);
}

TYPED_TEST(TestDeque, Const_Iterator_NotEqual_2) {
  typedef typename TestFixture::deque_type      deque_type;
  typedef typename TestFixture::allocator_type  allocator_type;
  typedef typename TestFixture::value_type      value_type;
  typedef typename TestFixture::size_type       size_type;
  typedef typename TestFixture::difference_type difference_type;
  typedef typename TestFixture::pointer         pointer;
  typedef typename TestFixture::const_pointer   const_pointer;
  typedef typename TestFixture::reference       reference;
  typedef typename TestFixture::const_reference const_reference;

  const deque_type x(300);
  int count = 0;
  typename deque_type::const_iterator b = x.begin();
  typename deque_type::const_iterator e = x.end();

  while (b != e) {
    ++count;
    ++b;
  }

  ASSERT_EQ(count, 300);
}

TYPED_TEST(TestDeque, Const_Iterator_Dereference_1) {
  typedef typename TestFixture::deque_type      deque_type;
  typedef typename TestFixture::allocator_type  allocator_type;
  typedef typename TestFixture::value_type      value_type;
  typedef typename TestFixture::size_type       size_type;
  typedef typename TestFixture::difference_type difference_type;
  typedef typename TestFixture::pointer         pointer;
  typedef typename TestFixture::const_pointer   const_pointer;
  typedef typename TestFixture::reference       reference;
  typedef typename TestFixture::const_reference const_reference;

  deque_type x(20);
  x[0] = 5;
  const deque_type y = x;
  //typename deque_type::const_iterator p = y.begin();

  //ASSERT_EQ(*p, 5);
  //p++;
  //ASSERT_EQ(*p, 0);
  //p--;
  //ASSERT_EQ(*p, 5);
}

// Note: This is a non-typed test
TEST(TestMyDeque, Const_Iterator_Arrow_1) {

  struct dummy {
    int x;
    int y;
    dummy() : x(1), y(2) {}
  };

  const my_deque<dummy> x(10);
  typename my_deque<dummy>::const_iterator b = x.begin();
   
  for (int i = 0; i < 10; ++i) {
    ASSERT_EQ(b->x, 1); 
    ASSERT_EQ(b->y, 2); 
    ++b;
  }
}

TYPED_TEST(TestDeque, Const_Iterator_PrePlusPlus_1) {
  typedef typename TestFixture::deque_type      deque_type;
  typedef typename TestFixture::allocator_type  allocator_type;
  typedef typename TestFixture::value_type      value_type;
  typedef typename TestFixture::size_type       size_type;
  typedef typename TestFixture::difference_type difference_type;
  typedef typename TestFixture::pointer         pointer;
  typedef typename TestFixture::const_pointer   const_pointer;
  typedef typename TestFixture::reference       reference;
  typedef typename TestFixture::const_reference const_reference;

  deque_type x(100);
  for (int i = 0; i < 100; ++i) {
    x[i] = i;
  }
  const deque_type y = x;
  typename deque_type::const_iterator p = y.begin();

  for (int i = 0; i < 100; ++i) {
    ASSERT_EQ(*p, i);
    ++p;
  }
}

TYPED_TEST(TestDeque, Const_Iterator_PostPlusPlus_1) {
  typedef typename TestFixture::deque_type      deque_type;
  typedef typename TestFixture::allocator_type  allocator_type;
  typedef typename TestFixture::value_type      value_type;
  typedef typename TestFixture::size_type       size_type;
  typedef typename TestFixture::difference_type difference_type;
  typedef typename TestFixture::pointer         pointer;
  typedef typename TestFixture::const_pointer   const_pointer;
  typedef typename TestFixture::reference       reference;
  typedef typename TestFixture::const_reference const_reference;

  deque_type x(100);
  for (int i = 0; i < 100; ++i) {
    x[i] = i;
  }
  const deque_type y = x;
  typename deque_type::const_iterator p = y.begin();

  for (int i = 0; i < 100; ++i) {
    ASSERT_EQ(*p, i);
    value_type temp = *(p++);
    ASSERT_EQ(temp, i);
  }
}

TYPED_TEST(TestDeque, Const_Iterator_PreMinusMinus_1) {
  typedef typename TestFixture::deque_type      deque_type;
  typedef typename TestFixture::allocator_type  allocator_type;
  typedef typename TestFixture::value_type      value_type;
  typedef typename TestFixture::size_type       size_type;
  typedef typename TestFixture::difference_type difference_type;
  typedef typename TestFixture::pointer         pointer;
  typedef typename TestFixture::const_pointer   const_pointer;
  typedef typename TestFixture::reference       reference;
  typedef typename TestFixture::const_reference const_reference;

  deque_type x(100);
  for (int i = 0; i < 100; ++i) {
    x[i] = i;
  }
  const deque_type y = x;
  typename deque_type::const_iterator p = y.begin();
  p += 99;

  for (int i = 0; i < 100; ++i) {
    ASSERT_EQ(*p, 99 - i);
    --p;
  }
}

TYPED_TEST(TestDeque, Const_Iterator_PostMinusMinus_1) {
  typedef typename TestFixture::deque_type      deque_type;
  typedef typename TestFixture::allocator_type  allocator_type;
  typedef typename TestFixture::value_type      value_type;
  typedef typename TestFixture::size_type       size_type;
  typedef typename TestFixture::difference_type difference_type;
  typedef typename TestFixture::pointer         pointer;
  typedef typename TestFixture::const_pointer   const_pointer;
  typedef typename TestFixture::reference       reference;
  typedef typename TestFixture::const_reference const_reference;

  deque_type x(100);
  for (int i = 0; i < 100; ++i) {
    x[i] = i;
  }
  const deque_type y = x;
  typename deque_type::const_iterator p = y.begin();
  p += 99;

  for (int i = 0; i < 100; ++i) {
    ASSERT_EQ(*p, 99 - i);
    value_type temp = *(p--);
    ASSERT_EQ(temp, 99 - i);
  }
}

TYPED_TEST(TestDeque, Const_Iterator_PlusEq_1) {
  typedef typename TestFixture::deque_type      deque_type;
  typedef typename TestFixture::allocator_type  allocator_type;
  typedef typename TestFixture::value_type      value_type;
  typedef typename TestFixture::size_type       size_type;
  typedef typename TestFixture::difference_type difference_type;
  typedef typename TestFixture::pointer         pointer;
  typedef typename TestFixture::const_pointer   const_pointer;
  typedef typename TestFixture::reference       reference;
  typedef typename TestFixture::const_reference const_reference;

  deque_type x(100);
  for (int i = 0; i < 100; ++i) {
    x[i] = i;
  }
  const deque_type y = x;
  typename deque_type::const_iterator i = y.begin();
  ASSERT_EQ(*i, 0);
  i += 10;
  ASSERT_EQ(*i, 10);
  i += 33;
  ASSERT_EQ(*i, 43);
  i += 27;
  ASSERT_EQ(*i, 70);
  i += 11;
  ASSERT_EQ(*i, 81);
  i += 18;
  ASSERT_EQ(*i, 99);
}

TYPED_TEST(TestDeque, Const_Iterator_MinusEq_1) {
  typedef typename TestFixture::deque_type      deque_type;
  typedef typename TestFixture::allocator_type  allocator_type;
  typedef typename TestFixture::value_type      value_type;
  typedef typename TestFixture::size_type       size_type;
  typedef typename TestFixture::difference_type difference_type;
  typedef typename TestFixture::pointer         pointer;
  typedef typename TestFixture::const_pointer   const_pointer;
  typedef typename TestFixture::reference       reference;
  typedef typename TestFixture::const_reference const_reference;

  deque_type x(100);
  for (int i = 0; i < 100; ++i) {
    x[i] = i;
  }
  const deque_type y = x;
  typename deque_type::const_iterator i = y.begin();

  i += 99;
  ASSERT_EQ(*i, 99);
  i -= 30;
  ASSERT_EQ(*i, 69);
  i -= 19;
  ASSERT_EQ(*i, 50);
  i -= 25;
  ASSERT_EQ(*i, 25);
  i -= 25;
  ASSERT_EQ(*i, 0);
}

TYPED_TEST(TestDeque, Resize_1) {
  typedef typename TestFixture::deque_type      deque_type;
  typedef typename TestFixture::allocator_type  allocator_type;
  typedef typename TestFixture::value_type      value_type;
  typedef typename TestFixture::size_type       size_type;
  typedef typename TestFixture::difference_type difference_type;
  typedef typename TestFixture::pointer         pointer;
  typedef typename TestFixture::const_pointer   const_pointer;
  typedef typename TestFixture::reference       reference;
  typedef typename TestFixture::const_reference const_reference;

  deque_type x(10);
  for(int i = 10; i < 15; ++i) {
    //cout << "pushing: " << i << endl;
    x.push_back(10);
    ASSERT_EQ(x[i], 10);
  }

  for(int i = 3; i < 15; ++i) {
    x.push_back(15);
  }

  ASSERT_EQ(x[10], 10);
}

TYPED_TEST(TestDeque, Resize_2) {
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

  x.resize(1);
  ASSERT_EQ(x.size(), 1);
  x[0] = -1;
  ASSERT_EQ(x[0], -1);
  pointer p1 = &(x[0]);

  x.resize(5);
  pointer p2 = &(x[0]);
  ASSERT_EQ(p1, p2);
  x[4] = -1;
  ASSERT_EQ(x[4], -1);
  ASSERT_EQ(x.size(), 5);

  x.resize(11);
  x[10] = -1;
  ASSERT_EQ(x[10], -1);

  ASSERT_EQ(x.size(), 11);
  ASSERT_EQ(x[0], -1);
  ASSERT_EQ(x[4], -1);
  ASSERT_EQ(x[10], -1);
}

TYPED_TEST(TestDeque, Resize_3) {
  typedef typename TestFixture::deque_type      deque_type;
  typedef typename TestFixture::allocator_type  allocator_type;
  typedef typename TestFixture::value_type      value_type;
  typedef typename TestFixture::size_type       size_type;
  typedef typename TestFixture::difference_type difference_type;
  typedef typename TestFixture::pointer         pointer;
  typedef typename TestFixture::const_pointer   const_pointer;
  typedef typename TestFixture::reference       reference;
  typedef typename TestFixture::const_reference const_reference;

  deque_type x(1); 
  ASSERT_EQ(x.size(), 1);
  x.resize(25);
  ASSERT_EQ(x.size(), 25);
  // cout << "here1" << endl;
  x[0] = 5;
  // cout << "here2" << endl;
  ASSERT_EQ(x[0], 5);
}

TYPED_TEST(TestDeque, Resize_4) {
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
  ASSERT_EQ(x.size(), 0);
  x.resize(94);
  ASSERT_EQ(x.size(), 94);
  x[0] = 5;
  ASSERT_EQ(x[0], 5);
}

TYPED_TEST(TestDeque, Resize_5) {
  typedef typename TestFixture::deque_type      deque_type;
  typedef typename TestFixture::allocator_type  allocator_type;
  typedef typename TestFixture::value_type      value_type;
  typedef typename TestFixture::size_type       size_type;
  typedef typename TestFixture::difference_type difference_type;
  typedef typename TestFixture::pointer         pointer;
  typedef typename TestFixture::const_pointer   const_pointer;
  typedef typename TestFixture::reference       reference;
  typedef typename TestFixture::const_reference const_reference;

  deque_type x(337); 
  x[0] = 5;
  ASSERT_EQ(x.size(), 337);
  x.resize(1);
  ASSERT_EQ(x.size(), 1);
  ASSERT_EQ(x[0], 5);
}

// TYPED_TEST(TestDeque, Swap_1) {
//   typedef typename TestFixture::deque_type      deque_type;
//   typedef typename TestFixture::allocator_type  allocator_type;
//   typedef typename TestFixture::value_type      value_type;
//   typedef typename TestFixture::size_type       size_type;
//   typedef typename TestFixture::difference_type difference_type;
//   typedef typename TestFixture::pointer         pointer;
//   typedef typename TestFixture::const_pointer   const_pointer;
//   typedef typename TestFixture::reference       reference;
//   typedef typename TestFixture::const_reference const_reference;

//   deque_type x;
//   for(int i = 0; i < 10; ++i) {
//     x.push_back(i);
//     ASSERT_EQ(x[i], i);
//   }

//   deque_type y;
//   int z = 0;
//   for(int j = 9; j >= 0; --j) {
//     y.push_back(j);
//     ASSERT_EQ(y[z++], j);
//   }
//   x.swap(y);

//   ASSERT_EQ(x[0], 9);
// }

TYPED_TEST(TestDeque, Copy_1) {
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
  for(int i = 0; i < 10; ++i) {
    x.push_back(i);
    ASSERT_EQ(x[i], i);
  }

  deque_type y = x;
  for(int i = 0; i < 10; ++i) {
    y.push_back(i);
    ASSERT_EQ(y[i], i);
  }
}

TYPED_TEST(TestDeque, Insert_1) {
  typedef typename TestFixture::deque_type      deque_type;
  typedef typename TestFixture::allocator_type  allocator_type;
  typedef typename TestFixture::value_type      value_type;
  typedef typename TestFixture::size_type       size_type;
  typedef typename TestFixture::difference_type difference_type;
  typedef typename TestFixture::pointer         pointer;
  typedef typename TestFixture::const_pointer   const_pointer;
  typedef typename TestFixture::reference       reference;
  typedef typename TestFixture::const_reference const_reference;
  //0 1 2 3 4 5 6 7 8 9
  //0 1 2 2 3 4 5 6 7 8 9

  deque_type x;
  for(int i = 0; i < 10; ++i) {
    x.push_back(i);
    ASSERT_EQ(x[i], i);
  } 
  ASSERT_EQ(x.size(), 10);
  typename deque_type::iterator y = x.begin();
  y++;
  y++;
  x.insert(y, 2);
  ASSERT_EQ(x[2], x[3]);
  ASSERT_EQ(x[x.size() - 1], 9);
  ASSERT_EQ(x.size(), 11);
}

TYPED_TEST(TestDeque, Insert_2) {
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
  typename deque_type::iterator y = x.begin();
  x.insert(y, 10);
  ASSERT_EQ(x[0], 10);
  ASSERT_EQ(x.size(), 1);
}

TYPED_TEST(TestDeque, Insert_3) {
  typedef typename TestFixture::deque_type      deque_type;
  typedef typename TestFixture::allocator_type  allocator_type;
  typedef typename TestFixture::value_type      value_type;
  typedef typename TestFixture::size_type       size_type;
  typedef typename TestFixture::difference_type difference_type;
  typedef typename TestFixture::pointer         pointer;
  typedef typename TestFixture::const_pointer   const_pointer;
  typedef typename TestFixture::reference       reference;
  typedef typename TestFixture::const_reference const_reference;
  deque_type x(10); 
  ASSERT_EQ(x.size(), 10);
  typename deque_type::iterator y = x.end();
  x.insert(y, 3);
  ASSERT_EQ(x.size(), 11);
  ASSERT_EQ(x[x.size() - 1], 3);
}

TYPED_TEST(TestDeque, Insert_4) {
  typedef typename TestFixture::deque_type      deque_type;
  typedef typename TestFixture::allocator_type  allocator_type;
  typedef typename TestFixture::value_type      value_type;
  typedef typename TestFixture::size_type       size_type;
  typedef typename TestFixture::difference_type difference_type;
  typedef typename TestFixture::pointer         pointer;
  typedef typename TestFixture::const_pointer   const_pointer;
  typedef typename TestFixture::reference       reference;
  typedef typename TestFixture::const_reference const_reference;
  deque_type x(15);
  ASSERT_EQ(x.size(), 15);
  typename deque_type::iterator y = x.begin();
  x.insert(y + 7, -333);
  ASSERT_EQ(x.size(), 16); 
  ASSERT_EQ(x[7], -333);
}

TYPED_TEST(TestDeque, Less_Than_1) {
  typedef typename TestFixture::deque_type      deque_type;
  typedef typename TestFixture::allocator_type  allocator_type;
  typedef typename TestFixture::value_type      value_type;
  typedef typename TestFixture::size_type       size_type;
  typedef typename TestFixture::difference_type difference_type;
  typedef typename TestFixture::pointer         pointer;
  typedef typename TestFixture::const_pointer   const_pointer;
  typedef typename TestFixture::reference       reference;
  typedef typename TestFixture::const_reference const_reference;
  //0 1 2 3 4
  //10 9 8 7 6
  deque_type x;
  for(value_type i = 0; i < 5; ++i) {
    x.push_back(i);
  }
  deque_type y; 
  for(value_type j = 10; j > 5; --j) {
    y.push_back(j);
  }
  ASSERT_EQ(*x.begin(), 0);
  ASSERT_EQ(*(x.end() - 1), 4);

  ASSERT_EQ(*y.begin(), 10);
  ASSERT_EQ(*(y.end() - 1), 6);

  ASSERT_TRUE(x < y);
}
//ToDO instances where x == y, and x > y

TYPED_TEST(TestDeque, Push_Front_1) {
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
  for(value_type i = 0; i < 5; ++i) {
    x.push_front(i);
  }
  ASSERT_EQ(x[0], 4);
  ASSERT_EQ(x[1], 3);
  ASSERT_EQ(x[2], 2);
  ASSERT_EQ(x[3], 1);
  ASSERT_EQ(x[4], 0);
}

TYPED_TEST(TestDeque, Push_Front_2) {
  typedef typename TestFixture::deque_type      deque_type;
  typedef typename TestFixture::allocator_type  allocator_type;
  typedef typename TestFixture::value_type      value_type;
  typedef typename TestFixture::size_type       size_type;
  typedef typename TestFixture::difference_type difference_type;
  typedef typename TestFixture::pointer         pointer;
  typedef typename TestFixture::const_pointer   const_pointer;
  typedef typename TestFixture::reference       reference;
  typedef typename TestFixture::const_reference const_reference;
  //  2 1 0 0 0 0 0 0 0 0 0 0 0 0 0 

  // deque_type x(9);
  // x.push_front(10);
  // x.push_front(10);
  // ASSERT_EQ(x.size(), 11);

  // ASSERT_EQ(x[0], 10);
  // ASSERT_EQ(x[1], 10);

  deque_type x(12);
  for(size_type i = 0; i < 1000; ++i) {
    x.push_front(i);
  }
  for(size_type j = 0; j < 1000; ++j) {
    ASSERT_EQ(x[j], 999 - j);
  }
}













