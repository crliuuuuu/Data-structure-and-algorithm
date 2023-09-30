/**
 * @file   Vector.h
 * @author Liu chenruo <1816655804@qq.com>
 * @date   Fri Oct 15 23:19:45
 * 
 * @brief  An inplementation of vector.
 *
 */


#ifndef _LcrVector_
#define _LcrVector_

#include <algorithm>
#include <new>

template <typename Object>
class Vector
{
 public:

  /**
   * Initializes the vector.
   */
  explicit Vector( int initSize = 0 ) : theSize{ initSize },
       theCapacity{ initSize + SPARE_CAPACITY }
    { objects = new Object[ theCapacity ]; }

  Vector( const Vector & rhs ) : theSize{ rhs.theSize },
       theCapacity{ rhs.theCapacity }, objects{ nullptr }
    {
      objects = new Object[ theCapacity ];
      for( int k = 0; k < theSize; ++k )
	objects[k] = rhs.objects[k];
    }

  Vector & operator= ( const Vector & rhs )
  {
    Vector copy = rhs;
    std::swap( *this, copy );
    return *this;
  }

  ~Vector()
    { delete [] objects; }

  Vector( Vector && rhs ) : theSize{ rhs.theSize },
    theCapacity{ rhs.theCapacity }, objects{ rhs.objects }
  {
    rhs.objects = nullptr;
    rhs.theSize = 0;
    rhs.theCapacity = 0;
  }

  Vector & operator= ( Vector && rhs )
  {
    std::swap( theSize, rhs.theSize );
    std::swap( theCapacity, rhs.theCapacity );
    std::swap( objects, rhs.objects );

    return *this;
  }

  /**
   * Reset the size of the vector.
   */
  void resize( int newSize )
  {
    if( newSize > theCapacity )
      reserve( newSize * 2 );
    theSize = newSize;
  }

  /**
   * Extends the capacity of the vector.
   */
  void reserve( int newCapacity )
  {
    if( newCapacity < theSize )
      return;

    Object *newArray = new Object[ newCapacity ];
    for (int k = 0; k < theSize; ++k )
      newArray[k] =  std::move( objects[k] );

    theCapacity = newCapacity;
    std::swap( objects, newArray ) ;
    delete [] newArray;
  }

  Object & operator[]( int index )
    { return objects[index]; }
  const Object & operator[]( int index ) const
    { return objects[index]; }

  /**
   * Empty means the vector has no element.
   */
  bool empty() const
    { return size( ) == 0; }
  int size() const
    { return theSize; }
  int capacity() const
    { return theCapacity; }

  /**
   * Adds x to the end of the vector.
   */
  void push_back( const Object & x )
  {
    if (theSize == theCapacity)
      reserve( 2 * theCapacity + 1 );
    objects[ theSize++ ] = x;
  }

  void push_back( Object && x )
  {
    if (theSize == theCapacity)
      reserve( 2* theCapacity +1 );
    objects[ theSize++ ] = std::move( x );
  }

  /**
   * Removes the object from at the end of the vector.
   */
  void pop_back()
  {
    --theSize;
  }

  /**
   * Returns the last element.
   */
  const Object & back () const
  {
    return objects[ theSize -1 ];
  }

  typedef Object * iterator;
  typedef const Object * const_iterator;

  /**
   * Returns an iterator representing the first element of the vector.
   */
  iterator begin()
    { return &objects[ 0 ]; }
  const_iterator begin() const
    { return &objects[ 0 ]; }

  /**
   * Returns an iterator representing the positon AFTER the last element
   * of the vector.
   */
  iterator end()
    { return &objects[ size() ]; }
  const_iterator end() const
    { return &objects[ size() ]; }                          

  // The size of the spare capacity of the vector;
  int SPARE_CAPACITY = 0;
  
 private:

  /**
   * @param theSize        The size of vector;
   *        theCapacity    The capacity of vector;
   */        
  int theSize;
  int theCapacity ;
  Object * objects;
  
};

#else
/// DO Nothing.
#endif
