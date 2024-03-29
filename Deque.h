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
    // cout << "entering copy" << endl;
    // cout << "*b: " << *b << " *e: " << *(--e) << endl;
    while (b != e) {
      // cout << "&*x: " << &*x << " *b: " << *b << endl;
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

      friend class my_deque;

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
        my_deque* _d;   //! Pointer to the deque over we're iterating 
        size_type _idx; //! Indexing into chunk table

      private:
        // -----
        // valid
        // -----

        bool valid () const {
          return true;
        }

      public:
        // -----------
        // operator ==
        // -----------

        /**
         * Compare two iterators for equality.
         * @param lhs An iterator reference 
         * @param rhs An iterator reference 
         */
        friend bool operator == (const iterator& lhs, const iterator& rhs) {
          return (lhs._d == rhs._d) && (lhs._idx == rhs._idx);
        }

        /**
         * Compare two iterators for inequality.
         * @param lhs An iterator reference 
         * @param rhs An iterator reference 
         */
        friend bool operator != (const iterator& lhs, const iterator& rhs) {
          return !(lhs == rhs);
        }

        // ----------
        // operator +
        // ----------

        /**
         * Increment this random access iterator by a given difference.
         * @param lhs An iterator instance
         * @param rhs Desired offset from the current position 
         * @return An iterator to the element offset from the start point
         */
        friend iterator operator + (iterator lhs, difference_type rhs) {
          return lhs += rhs;
        }

        // ----------
        // operator -
        // ----------

        /**
         * Decrement this random access iterator by a given difference.
         * @param lhs An iterator instance
         * @param rhs Desired offset from the current position 
         * @return An iterator to the element offset from the start point
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
         */
        iterator () : _d(NULL), _idx(0) {}

        /**
         * Specified Constructor.
         * @param d A pointer to the deque over which this iterates 
         * @param i The virtual index into the deque where this iterator points 
         */
        iterator (my_deque* d, size_type i) :
          _d(d),
          _idx(i)
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
         * Return a reference to the element currently pointed to by this 
         * iterator. 
         */
        reference operator * () const {
          return (*_d)[_idx];
        }

        // -----------
        // operator ->
        // -----------

        /**
         * Access members of the element to which this iterator points. 
         */
        pointer operator -> () const {
          return &**this;
        }

        // -----------
        // operator ++
        // -----------

        /**
         * Increment (Pre) where this iterator points by one position. 
         * @return A reference to this iterator
         */
        iterator& operator ++ () {
          _idx++;
          assert(valid());
          return *this;
        }

        /**
         * Increment (Post) where this iterator points by one position. 
         * @return A reference to this iterator
         */
        iterator operator ++ (int) {
          iterator x = *this;
          ++_idx;
          assert(valid());
          return x;
        }

        // -----------
        // operator --
        // -----------

        /**
         * Decrement (Pre) where this iterator points by one position. 
         * @return A reference to this iterator
         */
        iterator& operator -- () {
          --_idx;
          assert(valid());
          return *this;
        }

        /**
         * Decrement (Post) where this iterator points by one position. 
         * @return A reference to this iterator
         */
        iterator operator -- (int) {
          iterator x = *this;
          --_idx;
          assert(valid());
          return x;
        }

        // -----------
        // operator +=
        // -----------

        /**
         * Increment where this iterator points by d position s. 
         * @param d Positional offset to adjust this iterator by
         * @return A reference to this iterator
         */
        iterator& operator += (difference_type d) {
          _idx += d;
          assert(valid());
          return *this;
        }

        // -----------
        // operator -=
        // -----------

        /**
         * Decrement where this iterator points by d position s. 
         * @param d Positional offset to adjust this iterator by
         * @return A reference to this iterator
         */
        iterator& operator -= (difference_type d) {
          _idx -= d;
          assert(valid());
          return *this;
        }
    };

  public:
    // --------------
    // const_iterator
    // --------------

    class const_iterator {

      friend class my_deque;

      public:
        // --------
        // typedefs
        // --------

        typedef std::bidirectional_iterator_tag    iterator_category;
        typedef typename my_deque::value_type      value_type;
        typedef typename my_deque::difference_type difference_type;
        typedef typename my_deque::const_pointer   pointer;
        typedef typename my_deque::const_reference reference;

      private:
        // ----
        // data
        // ----
        my_deque* _d; //! Pointer to the deque over we're iterating 
        size_type _idx;           //! Indexing into chunk table

      private:
        // -----
        // valid
        // -----

        bool valid () const {
          return _d->valid();
        }

      public:
        // -----------
        // operator ==
        // -----------

        /**
         * Compare two const_iterators for equality.
         * @param lhs An const_iterator reference 
         * @param rhs An const_iterator reference 
         */
        friend bool operator == (const const_iterator& lhs, const const_iterator& rhs) {
          return (lhs._d == rhs._d) && (lhs._idx == rhs._idx);
        }

        /**
         * Compare two const_iterators for inequality.
         * @param lhs An const_iterator reference 
         * @param rhs An const_iterator reference 
         */
        friend bool operator != (const const_iterator& lhs, const const_iterator& rhs) {
          return !(lhs == rhs);
        }

        // ----------
        // operator +
        // ----------

        /**
         * Increment this const_iterator by a given difference.
         * @param lhs An const_iterator instance
         * @param rhs Desired offset from the current position 
         * @return A const_iterator to the element offset from the start point
         */
        friend const_iterator operator + (const_iterator lhs, difference_type rhs) {
          return lhs += rhs;
        }

        // ----------
        // operator -
        // ----------

        /**
         * Decrement this const_iterator by a given difference.
         * @param lhs An const_iterator instance
         * @param rhs Desired offset from the current position 
         * @return A const_iterator to the element offset from the start point
         */
        friend const_iterator operator - (const_iterator lhs, difference_type rhs) {
          return lhs -= rhs;
        }

      public:
        // -----------
        // constructor
        // -----------

        /**
         * Constructor 
         * @param: d A pointer to a deque instance
         * @param: i This iterator's virtual index into the deque
         */
        const_iterator (my_deque* d, size_type i) : _d(d), _idx(i) {
          assert(valid());
        }

        /**
         * Conversion Constructor 
         * @param: i An iterator instance 
         */
        const_iterator (iterator i) : _d(i._d), _idx(i._idx) {
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
         * Return a reference to the element currently pointed to by this 
         * const_iterator. 
         */
        reference operator * () const {
          return (*_d)[_idx];
        }

        // -----------
        // operator ->
        // -----------

        /**
         * Access members of the element to which this const_iterator 
         * points. 
         */
        pointer operator -> () const {
          return &**this;
        }

        // -----------
        // operator ++
        // -----------

        /**
         * Increment (Pre) where this const_iterator points by one position. 
         * @return A reference to this const_iterator
         */
        const_iterator& operator ++ () {
          ++_idx;
          assert(valid());
          return *this;
        }

        /**
         * Decrement (Post) where this const_iterator points by one position. 
         * @return A reference to this const_iterator
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
         * Decrement (Pre) where this const_iterator points by one position. 
         * @return A reference to this const_iterator
         */
        const_iterator& operator -- () {
          --_idx;
          assert(valid());
          return *this;
        }

        /**
         * Decrement (Post) where this const_iterator points by one position. 
         * @return A reference to this const_iterator
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
         * Increment where this const_iterator points by d position s. 
         * @param d Positional offset to adjust this const_iterator by
         * @return A reference to this const_iterator
         */
        const_iterator& operator += (difference_type d) {
          _idx += d;
          assert(valid());
          return *this;
        }

        // -----------
        // operator -=
        // -----------

        /**
         * Decrement where this const_iterator points by d position s. 
         * @param d Positional offset to adjust this const_iterator by
         * @return A reference to this const_iterator
         */
        const_iterator& operator -= (difference_type d) {
          _idx -= d;
          assert(valid());
          return *this;
        }
    };

  public:
    // -----------
    // operator ==
    // -----------

    /**
     * Compare two deques for equality.
     * @param lhs A deque reference 
     * @param rhs A deque reference 
     */
    friend bool operator == (const my_deque& lhs, const my_deque& rhs) {      
      return std::equal(lhs.begin(), lhs.end(), rhs.begin());

    }

    // ----------
    // operator <
    // ----------

    /**
     * Compare if one deque is less a second.
     * @param lhs A deque reference 
     * @param rhs A deque reference 
     */
    friend bool operator < (const my_deque& lhs, const my_deque& rhs) {
      return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

  private:
    // ----
    // data
    // ----

    //! Allocates data chunks
    allocator_type _chunk_a;

    //! Allocates chunk table entries (each of which points to a data chunk)
    typename allocator_type::template rebind<T*>::other _table_a;
    
    T**       _table_p;     //! Handle for the chunk table
    size_type _table_size;  //! Number of entries in the chunk table
  
    //! "Physical" begining
    size_type _b_table_idx; 
    size_type _b_chunk_idx;

    //! Virtual begining and end
    iterator _b;            
    iterator _e;
    iterator _l;   

      

  private:
    // -----
    // valid
    // -----

    bool valid () const {
      bool v = (!_b._idx && !_e._idx && !_l._idx) || 
               ((_b._idx <= _e._idx) && (_e._idx <= _l._idx));
      // if (!v) {
      //   cout << "Invalid Deque: " << endl;
      //   cout << "\t_b._idx: " << _b._idx << endl;
      //   cout << "\t_e._idx: " << _e._idx << endl;
      //   cout << "\t_l._idx: " << _l._idx << endl;
      // }
      return v;
    }

  public:
    // ------------
    // constructors
    // ------------

    /**
     * Default Constructor: An Empty Deque
     */
    explicit my_deque (const allocator_type& a = allocator_type()) 
      : my_deque(0, value_type(), a)
    {
      assert(size() == 0);
      assert(_table_size == 0);
      assert(_b_table_idx == 0);
      assert(_b_chunk_idx == 0);
      assert(valid());
    }

    /**
     * Construct a deque of the specified size.
     */
    explicit my_deque (size_type s, const_reference v = value_type(), 
                       const allocator_type& a = allocator_type()) {
      // Create chunk table
      _table_size = (s / CHUNK_SIZE);
      if((s % CHUNK_SIZE) != 0)
        _table_size += 1;
      //cout << "_table_size: " << _table_size << endl;
      _table_p = _table_a.allocate(_table_size);
      uninitialized_fill(_table_a, _table_p, _table_p + _table_size, pointer());

      // Allocate chunks and map them into the table
      for (size_type i = 0; i < _table_size; ++ i) {
        pointer _chunk_p = _chunk_a.allocate(CHUNK_SIZE);
        uninitialized_fill(_chunk_a, _chunk_p, _chunk_p + CHUNK_SIZE, v);
        _table_p[i] = _chunk_p;
      }

      _b_table_idx = 0;
      _b_chunk_idx = 0;

      _b = iterator(this, 0);
      _e = iterator(this, s);
      _l = iterator(this, _table_size * CHUNK_SIZE);

      assert(valid());
    }

    /**
     * Copy Constructor.
     * @param that The deque instance to copy 
     */
    my_deque (const my_deque& that) : _chunk_a(that._chunk_a) {
      _table_size = (that.size() / CHUNK_SIZE);
      if((that.size() % CHUNK_SIZE) != 0)
        _table_size += 1;
      _table_p = _table_a.allocate(_table_size);
      uninitialized_fill(_table_a, _table_p, _table_p + _table_size, pointer());

      // Allocate chunks and map them into the table
      for (size_type i = 0; i < _table_size; ++ i) {
        pointer _chunk_p = _chunk_a.allocate(CHUNK_SIZE);
        uninitialized_fill(_chunk_a, _chunk_p, _chunk_p + CHUNK_SIZE, value_type());
        _table_p[i] = _chunk_p;
      }

      _b_table_idx = 0;
      _b_chunk_idx = 0;

      _b = iterator(this, 0);
      _e = iterator(this, that.size());
      _l = iterator(this, _table_size * CHUNK_SIZE);


      std::copy(that.begin(), that.end(), begin());
      assert(valid());
    }

    // ----------
    // destructor
    // ----------

    /**
     * Deque destructor. Frees all allocated memory. 
     */
    ~my_deque () {
      // Destroy and Deallocate every chunk
      for (size_type i = 0; i < _table_size; ++i) {
        pointer chunk_p = _table_p[i];
        destroy(_chunk_a, chunk_p, chunk_p + CHUNK_SIZE);
        _chunk_a.deallocate(chunk_p, CHUNK_SIZE);
      }

      // Destroy and Deallocate the chunk table
      destroy(_table_a, _table_p, _table_p + _table_size);
      _table_a.deallocate(_table_p, _table_size);
      
      _b._idx = _e._idx = _l._idx = 0;
      _table_size = 0;
      _table_p = NULL;

      assert(valid());
    }

    // ----------
    // operator =
    // ----------

    /**
     * Copy Assignment. Make this deque identical to the given deque. 
     */
    my_deque& operator = (const my_deque& rhs) {

      // CASE I: This is That
      if (this == &rhs) {
        return *this;
      }

      // CASE II: This is same size as rhs
      if (size() == rhs.size()) {
        std::copy(rhs.begin(), rhs.end(), begin());
      }

      // CASE III: Everything Else
      else {
        resize(rhs.size());  
        std::copy(rhs.begin(), rhs.end(), begin());
      } 

      /*
      // CASE III: Rhs is smaller than this
      else if (size() > rhs.size()) {
        resize(rhs.size());
        std::copy(rhs.begin(), rhs.end(), begin());
      }
    
      // CASE IV: Rhs is bigger than this, but no allocation needed
      else if (rhs.size() <= capacity()) {
      }
      */

      assert(valid());
      return *this;
    }

    // -----------
    // operator []
    // -----------

    /**
     * Access the element at the specified deque index. 
     * @param index A virtual index into this deque
     * @return An l-val reference to the element
     */
    reference operator [] (size_type index) {
      // cout << "subscript(" << index << ")" << endl;
      size_type table_offset = index / CHUNK_SIZE;
      size_type chunk_offset = index % CHUNK_SIZE;

      // cout << "table offset, chunk_offset: " << "(" << table_offset << ", " << chunk_offset << ")" << endl;

      // cout << "_b_table_idx: " << _b_table_idx << endl;
      size_type table_idx = _b_table_idx + table_offset;
      size_type chunk_idx = _b_chunk_idx + chunk_offset;

      if (chunk_idx >= CHUNK_SIZE) {
        chunk_idx %= CHUNK_SIZE;
        ++table_idx;
      }

      // cout << "table index, chunk index: " << "(" << table_idx << ", " << chunk_idx << ")" << endl;

      return _table_p[table_idx][chunk_idx]; 
    }

    /**
     * Get a const reference to the deque element at the given index. 
     */
    const_reference operator [] (size_type index) const {
      return const_cast<my_deque*>(this)->operator[](index);
    }

    // --
    // at
    // --

    /**
     * Get a reference to the deque element at the given index. 
     * @throws out_of_range exception if the index is out of bounds
     */
    reference at (size_type index) {
      if(index >= size())
        throw std::out_of_range("deque");
      return (*this)[index];
    }

    /**
     * Get a const_reference to the deque element at the given index. 
     * @throws out_of_range exception if the index is out of bounds
     */
    const_reference at (size_type index) const {
      return const_cast<my_deque*>(this)->at(index);
    }

    // ----
    // back
    // ----

    /**
     * Access the last element
     */
    reference back () {
      assert(!empty());
      typename my_deque::iterator e = (*this).end();
      --e;
      return *e;
    }

    /**
     * Return a non-modifiable reference to the last element of this deque. 
     */
    const_reference back () const {
      assert(!empty());
      return const_cast<my_deque*>(this)->back();
    }

    // -----
    // begin
    // -----

    /**
     * Return an iterator to the beginning of this deque.
     */
    iterator begin () {
      return _b;
    }

    /**
     * Return a const_iterator to the beginning of this deque.
     */
    const_iterator begin () const {
      return const_iterator(_b);
    }

    // -----
    // clear
    // -----

    /**
     * Remove all elements from this deque. 
     */
    void clear () {
      resize(0);
      assert(valid());
    }

    // -----
    // empty
    // -----

    /**
     * Determine if this elements has no elements. 
     */
    bool empty () const {
      return !size();
    }

    // ---
    // end
    // ---

    /**
     * Return an iterator to the end of this deque.
     */
    iterator end () {
      return _e;
    }

    /**
     * Return an const_iterator to the end of this deque.
     */
    const_iterator end () const {
      return const_iterator(_e);
    }

    // -----
    // erase
    // -----

    /**
     * Removes the element at the position indicated by the given iterator. 
     */
    iterator erase (iterator i) {
      while(i != _e - 1) {
        *i = *(i + 1);  
        ++i;
      }
      --_e;
      assert(valid());
      return iterator();
    }

    // -----
    // front
    // -----

    /**
     * Returns a reference to the first element in the deque. 
     */
    reference front () {
      assert(!empty());
      return *begin();
    }

    /**
     * Returns a non-modifiable reference to the first element in the deque. 
     */
    const_reference front () const {
      return const_cast<my_deque*>(this)->front();
    }

    // ------
    // insert
    // ------

    /**
     * Insert the a value before the location pointed to by the given iterator
     * @param i An iterator specifying the insert position.
     * @param v The element to insert
     * @return An iterator pointing to the inserted value
     */
    iterator insert (iterator i, const_reference v) {
      resize(size() + 1); 
      iterator e = end();
      while(--e != i) {
        *e = *(e - 1);
      }
      *i = v; 
      assert(valid()); 
      return i;
      // return iterator();
    }

    // ---
    // pop
    // ---

    /**
     * Removes the last element of the deque. 
     */
    void pop_back () {
      assert(!empty());
      resize(size() - 1);
      assert(valid());
    }

    /**
     * Removes the first element of this deque. 
     */
    void pop_front () {
      ++_b_chunk_idx;
      if (_b_chunk_idx > CHUNK_SIZE) {
        _b_chunk_idx = 0;
        ++_b_table_idx;
      }
      --_e;
      --_l;
      assert(valid());
    }

    // ----
    // push
    // ----

    /**
     * Appends the given element value to the end of the deque. 
     * @param v The element value
     * @return void
     */
    void push_back (const_reference v) {
      if(_e == _l) {
        resize(size() + 1);
        *(_e - 1) = v;
      }
      else {
        *_e = v;
        _e++;
      }
      assert(valid());
    }

    /**
     * Appends the given element value to the front of the deque. 
     * @param v The element value
     * @return void
     */
    void push_front (const_reference v) {
      if(_b_table_idx == 0 && _b_chunk_idx == 0) {
        T** tmp = _table_p;
        _table_p = _table_a.allocate(size() + 1);
        _table_size++;
        uninitialized_fill(_table_a, _table_p, _table_p + _table_size, pointer());
        std::copy(tmp, tmp + _table_size - 1, _table_p + 1);
        pointer _chunk_p = _chunk_a.allocate(CHUNK_SIZE);
        uninitialized_fill(_chunk_a, _chunk_p, _chunk_p + CHUNK_SIZE, value_type());
        _table_p[0] = _chunk_p;
        _b_table_idx = 0;
        _b_chunk_idx = CHUNK_SIZE - 1;

        // Destroy and Deallocate the old table
        destroy(_table_a, tmp, tmp + _table_size - 1);
        _table_a.deallocate(tmp, _table_size - 1);
      }
      else {
        if(--_b_chunk_idx < 0) {
          --_b_table_idx;
          _b_chunk_idx = CHUNK_SIZE - 1;
        } 
      }
      ++_e;
      ++_l;
      *_b = v; 
      assert(valid());
    }

    // ------
    // resize
    // ------

    /**
     * Resizes the deque to contain s elements. If the current size is 
     * greater than s, the container is reduced to its first count 
     * elements as if by repeatedly calling pop_back(). 
     * @param s The desired new size of this container.
     * @param v The value to assign elements if expanding size.
     * @return void
     */
    void resize (size_type s, const_reference v = value_type()) {
      // cout << "Entering resize()" << endl;
      // cout << "Requested size : " << s << " current size: " << size() << endl;

      // CASE I: Requested size is exactly existing size
      if (s == size()) {
        return;
      }

      size_type new_table_size = (s / CHUNK_SIZE);
      if((s % CHUNK_SIZE) != 0 || (size() == 0))
        new_table_size++;

      // CASE II: Requested size is smaller than existing size
      if (s < size()) {
        _e = _b + s; 
        // TODO: Is it ok we don't destroy anything? I think so.
      }

      // CASE III: Requested size is greater than existing size but smaller than capacity
      else if (s < _l._idx) {
        _e = uninitialized_fill(_chunk_a, end(), begin() + s, v);
      }

      // CASE IV: Requested size is greater than existing capacity
      else {
        T** tmp = _table_p;
        // Allocate a new chunk table
        _table_p = _table_a.allocate(new_table_size);
        uninitialized_fill(_table_a, _table_p, _table_p + new_table_size, pointer());

        // Copy in the old chunk table
        std::copy(tmp, tmp + _table_size, _table_p);

        // Add necessary additional chunks and map them into the chunk table 
        size_type num_new_chunks = new_table_size - _table_size;
        for (size_type i = 0; i < num_new_chunks; ++ i) {
          pointer _chunk_p = _chunk_a.allocate(CHUNK_SIZE); 
          uninitialized_fill(_chunk_a, _chunk_p, _chunk_p + CHUNK_SIZE, v);
          _table_p[_table_size + i] = _chunk_p;
        }

        // Destroy and Deallocate the old table
        destroy(_table_a, tmp, tmp + _table_size);
        _table_a.deallocate(tmp, _table_size);

        _table_size = new_table_size;
        _l += CHUNK_SIZE * num_new_chunks;
        _e = _b + s;
      }
      assert(valid());
    }
    
    // TODO: COMMENT OUT AFTER DEV
    // void printChunkTable() {
    //   cout << "Chunk table has " << _table_size << " entries: " << endl;
    //   for (size_t i = 0; i < _table_size; ++i) {
    //     cout << "\t" << i << ": " << _table_p[i] << endl; 
    //   }
    // } 

      
    // ----
    // size
    // ----

    /**
     * Return the number of elements in this deque. 
     */
    size_type size () const {
      return _e._idx - _b._idx;
    }

    // ----
    // swap
    // ----

    /**
     * Exchanges the contents of this deque with those of other. 
     * Does not invoke any move, copy, or swap operations on individual elements.
     */
    void swap (my_deque& that) {
      if(_chunk_a == that._chunk_a) {
         std::swap(_b._idx, that._b._idx);
         std::swap(_e._idx, that._e._idx);
         std::swap(_l._idx, that._l._idx);
        
         std::swap(_table_a, that._table_a);
         std::swap(_b_table_idx, that._b_table_idx);
         std::swap(_b_chunk_idx, that._b_chunk_idx);
         std::swap(_table_size, that._table_size);

         T** p1 = _table_p;
         T** p2 = that._table_p;
         std::swap(_table_p, that._table_p);
         assert(_table_p == p2);
         assert(that._table_p == p1);
         assert(begin()._idx == 0);
      }
      else {
        my_deque x(*this);
        *this = that;
        that = x;
      }
      assert(valid());
  }
};

#endif // Deque_h
