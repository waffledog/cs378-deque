// ----------------------
// projects/deque/Deque.h
// Copyright (C) 2014
// Glenn P. Downing
// ----------------------

#ifndef Deque_h
#define Deque_h

// --------
// includes
// --------

#include <algorithm> // copy, equal, lexicographical_compare, max, swap
#include <cassert>   // assert
#include <iterator>  // iterator, bidirectional_iterator_tag
#include <memory>    // allocator
#include <stdexcept> // out_of_range
#include <utility>   // !=, <=, >, >=

#define CHUNK_SIZE 10

// -----
// using
// -----

using std::rel_ops::operator!=;
using std::rel_ops::operator<=;
using std::rel_ops::operator>;
using std::rel_ops::operator>=;

using std::cout;
using std::endl;

// -------
// destroy
// -------

template <typename A, typename BI>
BI destroy (A& a, BI b, BI e) {
  while (b != e) {
    --e;
    a.destroy(&*e);
  }
  return b;}

// ------------------
// uninitialized_copy
// ------------------

template <typename A, typename II, typename BI>
BI uninitialized_copy (A& a, II b, II e, BI x) {
  BI p = x;
  try {
    while (b != e) {
      a.construct(&*x, *b);
      ++b;
      ++x;
    }
  }
  catch (...) {
    destroy(a, p, x);
    throw;
  }
  return x;}

// ------------------
// uninitialized_fill
// ------------------

template <typename A, typename BI, typename U>
BI uninitialized_fill (A& a, BI b, BI e, const U& v) {
  BI p = b;
  try {
    while (b != e) {
      a.construct(&*b, v);
      ++b;
    }
  }
  catch (...) {
    destroy(a, p, b);
    throw;
  }
  return e;
}

// -------
// my_deque
// -------

template < typename T, typename A = std::allocator<T> >
class my_deque {
  public:
    // --------
    // typedefs
    // --------

    typedef A                                        allocator_type;
    typedef typename allocator_type::value_type      value_type;

    typedef typename allocator_type::size_type       size_type;
    typedef typename allocator_type::difference_type difference_type;

    typedef typename allocator_type::pointer         pointer;
    typedef typename allocator_type::const_pointer   const_pointer;

    typedef typename allocator_type::reference       reference;
    typedef typename allocator_type::const_reference const_reference;

  public:
    // --------
    // iterator
    // --------

    class iterator {
      public:
        // --------
        // typedefs
        // --------

        typedef std::bidirectional_iterator_tag    iterator_category;
        typedef typename my_deque::value_type      value_type;
        typedef typename my_deque::difference_type difference_type;
        typedef typename my_deque::pointer         pointer;
        typedef typename my_deque::reference       reference;

      private:
        // ----
        // data
        // ----
        my_deque<T, A>* _d;   //! Pointer to the deque over we're iterating 
        size_type _table_idx; //! Indexing into chunk table
        size_type _chunk_idx; //! Indexing into a chunk

      private:
        // -----
        // valid
        // -----

        bool valid () const {
          // <your code>
          return true;
        }

      public:
        // -----------
        // operator ==
        // -----------

        /**
         * <your documentation>
         */
        friend bool operator == (const iterator& lhs, const iterator& rhs) {
          // <your code>
          return true;
        }

        /**
         * <your documentation>
         */
        friend bool operator != (const iterator& lhs, const iterator& rhs) {
          return !(lhs == rhs);
        }

        // ----------
        // operator +
        // ----------

        /**
         * <your documentation>
         */
        friend iterator operator + (iterator lhs, difference_type rhs) {
          return lhs += rhs;
        }

        // ----------
        // operator -
        // ----------

        /**
         * <your documentation>
         */
        friend iterator operator - (iterator lhs, difference_type rhs) {
          return lhs -= rhs;
        }

      public:
        // -----------
        // constructor
        // -----------

        /**
         * Default constructor
         * <your documentation>
         */
        iterator () : _d(NULL), _table_idx(0), _chunk_idx(0) {}

        /**
         * <your documentation>
         */
        iterator (my_deque<T, A>* d, size_type table_idx, size_type chunk_idx) :
          _d(d),
          _table_idx(table_idx),
          _chunk_idx(chunk_idx)
        {
          assert(valid());
        }

        // Default copy, destructor, and copy assignment.
        // iterator (const iterator&);
        // ~iterator ();
        // iterator& operator = (const iterator&);

        // ----------
        // operator *
        // ----------

        /**
         * <your documentation>
         */
        reference operator * () const {
          // <your code>
          // dummy is just to be able to compile the skeleton, remove it
          static value_type dummy;
          return dummy;
        }

        // -----------
        // operator ->
        // -----------

        /**
         * <your documentation>
         */
        pointer operator -> () const {
          return &**this;
        }

        // -----------
        // operator ++
        // -----------

        /**
         * <your documentation>
         */
        iterator& operator ++ () {
          // <your code>
          assert(valid());
          return *this;
        }

        /**
         * <your documentation>
         */
        iterator operator ++ (int) {
          iterator x = *this;
          ++(*this);
          assert(valid());
          return x;
        }

        // -----------
        // operator --
        // -----------

        /**
         * <your documentation>
         */
        iterator& operator -- () {
          // <your code>
          assert(valid());
          return *this;
        }

        /**
         * <your documentation>
         */
        iterator operator -- (int) {
          iterator x = *this;
          --(*this);
          assert(valid());
          return x;
        }

        // -----------
        // operator +=
        // -----------

        /**
         * <your documentation>
         */
        iterator& operator += (difference_type d) {
          // <your code>
          assert(valid());
          return *this;
        }

        // -----------
        // operator -=
        // -----------

        /**
         * <your documentation>
         */
        iterator& operator -= (difference_type d) {
          // <your code>
          assert(valid());
          return *this;
        }
    };

  public:
    // --------------
    // const_iterator
    // --------------

    class const_iterator {
      public:
        // --------
        // typedefs
        // --------

        typedef std::bidirectional_iterator_tag   iterator_category;
        typedef typename my_deque::value_type      value_type;
        typedef typename my_deque::difference_type difference_type;
        typedef typename my_deque::const_pointer   pointer;
        typedef typename my_deque::const_reference reference;

      private:
        // ----
        // data
        // ----

        // <your data>

      private:
        // -----
        // valid
        // -----

        bool valid () const {
          // <your code>
          return true;
        }

      public:
        // -----------
        // operator ==
        // -----------

        /**
         * <your documentation>
         */
        friend bool operator == (const const_iterator& lhs, const const_iterator& rhs) {
          // <your code>
          return true;
        }

        /**
         * <your documentation>
         */
        friend bool operator != (const const_iterator& lhs, const const_iterator& rhs) {
          return !(lhs == rhs);
        }

        // ----------
        // operator +
        // ----------

        /**
         * <your documentation>
         */
        friend const_iterator operator + (const_iterator lhs, difference_type rhs) {
          return lhs += rhs;
        }

        // ----------
        // operator -
        // ----------

        /**
         * <your documentation>
         */
        friend const_iterator operator - (const_iterator lhs, difference_type rhs) {
          return lhs -= rhs;
        }

      public:
        // -----------
        // constructor
        // -----------

        /**
         * <your documentation>
         */
        const_iterator (/* <your arguments> */) {
          // <your code>
          assert(valid());
        }

        // Default copy, destructor, and copy assignment.
        // const_iterator (const const_iterator&);
        // ~const_iterator ();
        // const_iterator& operator = (const const_iterator&);

        // ----------
        // operator *
        // ----------

        /**
         * <your documentation>
         */
        reference operator * () const {
          // <your code>
          // dummy is just to be able to compile the skeleton, remove it
          static value_type dummy;
          return dummy;
        }

        // -----------
        // operator ->
        // -----------

        /**
         * <your documentation>
         */
        pointer operator -> () const {
          return &**this;
        }

        // -----------
        // operator ++
        // -----------

        /**
         * <your documentation>
         */
        const_iterator& operator ++ () {
          // <your code>
          assert(valid());
          return *this;
        }

        /**
         * <your documentation>
         */
        const_iterator operator ++ (int) {
          const_iterator x = *this;
          ++(*this);
          assert(valid());
          return x;
        }

        // -----------
        // operator --
        // -----------

        /**
         * <your documentation>
         */
        const_iterator& operator -- () {
          // <your code>
          assert(valid());
          return *this;
        }

        /**
         * <your documentation>
         */
        const_iterator operator -- (int) {
          const_iterator x = *this;
          --(*this);
          assert(valid());
          return x;
        }

        // -----------
        // operator +=
        // -----------

        /**
         * <your documentation>
         */
        const_iterator& operator += (difference_type) {
          // <your code>
          assert(valid());
          return *this;
        }

        // -----------
        // operator -=
        // -----------

        /**
         * <your documentation>
         */
        const_iterator& operator -= (difference_type) {
          // <your code>
          assert(valid());
          return *this;
        }
    };

  public:
    // -----------
    // operator ==
    // -----------

    /**
     * <your documentation>
     */
    friend bool operator == (const my_deque& lhs, const my_deque& rhs) {
      // <your code>
      // you must use std::equal()
      return true;
    }

    // ----------
    // operator <
    // ----------

    /**
     * <your documentation>
     */
    friend bool operator < (const my_deque& lhs, const my_deque& rhs) {
      // <your code>
      // you must use std::lexicographical_compare()
      return true;
    }

  private:
    // ----
    // data
    // ----

    //! Allocates data chunks
    allocator_type _chunk_a;

    //! Allocates chunk table entries (each of which points to a data chunk)
    typename allocator_type::template rebind<T*>::other _table_a;

    //! Handle for the chunk table
    T** _table_p;

    iterator _b; // Begining
    iterator _e; // End
    iterator _l; // Last element of last chunk. For capacity calculation.

  private:
    // -----
    // valid
    // -----

    bool valid () const {
      // <your code>
      return true;
    }

  public:
    // ------------
    // constructors
    // ------------

    /**
     * <your documentation>
     */
    explicit my_deque (const allocator_type& a = allocator_type()) {
      my_deque(0, value_type(), a);
      assert(valid());
    }

    /**
     * <your documentation>
     */
    explicit my_deque (size_type s, const_reference v = value_type(), 
                       const allocator_type& a = allocator_type()) {
      cout << "Entering my_deque constructor" << endl;
      cout << "s: " << s << endl;

      // Create chunk table
      size_type num_chunks = s / CHUNK_SIZE;
      cout << "num_chunks: " << num_chunks << endl;
      _table_p = _table_a.allocate(num_chunks);
      uninitialized_fill(_table_a, _table_p, _table_p + num_chunks, pointer());

      // Allocate chunks and map them into the table
      for (size_type i = 0; i < num_chunks; ++ i) {
        cout << "allocating chunk " << i << endl;
        pointer _chunk_p = _chunk_a.allocate(CHUNK_SIZE);
        uninitialized_fill(_chunk_a, _chunk_p, _chunk_p + CHUNK_SIZE, v);
        _table_p[i] = _chunk_p;
      }

      // TODO: Set _b and _e properly to be some middle range of the entire allocation
      _b = iterator(this, 0, 0);
      _e = iterator(this, num_chunks - 1, CHUNK_SIZE);
      _l = iterator(this, num_chunks - 1, CHUNK_SIZE -1);
      

      assert(valid());
    }

    /**
     * <your documentation>
     */
    my_deque (const my_deque& that) {
      // <your code>
      assert(valid());
    }

    // ----------
    // destructor
    // ----------

    /**
     * <your documentation>
     */
    ~my_deque () {
      // <your code>
      assert(valid());
    }

    // ----------
    // operator =
    // ----------

    /**
     * <your documentation>
     */
    my_deque& operator = (const my_deque& rhs) {
      // <your code>
      assert(valid());
      return *this;
    }

    // -----------
    // operator []
    // -----------

    /**
     * <your documentation>
     */
    reference operator [] (size_type index) {
      // <your code>
      // dummy is just to be able to compile the skeleton, remove it
      static value_type dummy;
      return dummy;
    }

    /**
     * <your documentation>
     */
    const_reference operator [] (size_type index) const {
      return const_cast<my_deque*>(this)->operator[](index);
    }

    // --
    // at
    // --

    /**
     * <your documentation>
     */
    reference at (size_type index) {
      // <your code>
      // dummy is just to be able to compile the skeleton, remove it
      static value_type dummy;
      return dummy;
    }

    /**
     * <your documentation>
     */
    const_reference at (size_type index) const {
      return const_cast<my_deque*>(this)->at(index);
    }

    // ----
    // back
    // ----

    /**
     * <your documentation>
     */
    reference back () {
      // <your code>
      // dummy is just to be able to compile the skeleton, remove it
      static value_type dummy;
      return dummy;
    }

    /**
     * <your documentation>
     */
    const_reference back () const {
      return const_cast<my_deque*>(this)->back();
    }

    // -----
    // begin
    // -----

    /**
     * <your documentation>
     */
    iterator begin () {
      // <your code>
      return iterator(/* <your arguments> */);
    }

    /**
     * <your documentation>
     */
    const_iterator begin () const {
      // <your code>
      return const_iterator(/* <your arguments> */);
    }

    // -----
    // clear
    // -----

    /**
     * <your documentation>
     */
    void clear () {
      // <your code>
      assert(valid());
    }

    // -----
    // empty
    // -----

    /**
     * <your documentation>
     */
    bool empty () const {
      return !size();
    }

    // ---
    // end
    // ---

    /**
     * <your documentation>
     */
    iterator end () {
      // <your code>
      return iterator(/* <your arguments> */);
    }

    /**
     * <your documentation>
     */
    const_iterator end () const {
      // <your code>
      return const_iterator(/* <your arguments> */);
    }

    // -----
    // erase
    // -----

    /**
     * <your documentation>
     */
    iterator erase (iterator) {
      // <your code>
      assert(valid());
      return iterator();
    }

    // -----
    // front
    // -----

    /**
     * <your documentation>
     */
    reference front () {
      // <your code>
      // dummy is just to be able to compile the skeleton, remove it
      static value_type dummy;
      return dummy;
    }

    /**
     * <your documentation>
     */
    const_reference front () const {
      return const_cast<my_deque*>(this)->front();
    }

    // ------
    // insert
    // ------

    /**
     * <your documentation>
     */
    iterator insert (iterator, const_reference) {
      // <your code>
      assert(valid());
      return iterator();
    }

    // ---
    // pop
    // ---

    /**
     * <your documentation>
     */
    void pop_back () {
      // <your code>
      assert(valid());
    }

    /**
     * <your documentation>
     */
    void pop_front () {
      // <your code>
      assert(valid());
    }

    // ----
    // push
    // ----

    /**
     * <your documentation>
     */
    void push_back (const_reference) {
      // <your code>
      assert(valid());
    }

    /**
     * <your documentation>
     */
    void push_front (const_reference) {
      // <your code>
      assert(valid());
    }

    // ------
    // resize
    // ------

    /**
     * <your documentation>
     */
    void resize (size_type s, const_reference v = value_type()) {
      // <your code>
      assert(valid());
    }

    // ----
    // size
    // ----

    /**
     * <your documentation>
     */
    size_type size () const {
      // <your code>
      return 0;
    }

    // ----
    // swap
    // ----

    /**
     * <your documentation>
     */
    void swap (my_deque&) {
      // <your code>
      assert(valid());
    }
};

#endif // Deque_h
