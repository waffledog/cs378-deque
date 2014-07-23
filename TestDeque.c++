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
  for (int i = 0; i < 40; ++i) {
    x[i] = 33;
    y[i] = 33;
  }

  ASSERT_EQ(x, y);
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
  //cout << "PushBack_1: " << x.size() << endl;
  for (int i = 10; i < 15; ++i) {
    cout << "PushBack_1: pushing value: " << i << endl;
    x.push_back(i);
    ASSERT_EQ(x[i], i);

    // x.push_front(i);
  }
  const size_type s = x.size();
  ASSERT_EQ(15, s);
}

TYPED_TEST(TestDeque, Constructor_1) {
  typedef typename TestFixture::deque_type      deque_type;
  deque_type x(56);
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

// TODO: Test Deque Copy Constructor

// TODO: Test Deque Copy Assignment 

// TODO: Test Deque at() 

// TODO: Test Deque const_reference at() 

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

// TODO: Test Deque const_reference back() 

// TODO: Test Deque clear() 

// TODO: Test Deque end() 

// TODO: Test Deque const_iterator end() 

// TODO: Test Deque erase() 

// TODO: Test Deque insert() 

// TODO: Test Deque pop_back() 

// TODO: Test Deque pop_front() 

// TODO: Test Deque push_back() 

// TODO: Test Deque push_front() 

// TODO: Test Deque resize() 

// TODO: Test Deque swap() 

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

TYPED_TEST(TestDeque, Iterator_PrePluPlus_1) {
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
  cout << "here1" << endl;
  x[0] = 5;
  cout << "here2" << endl;
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
