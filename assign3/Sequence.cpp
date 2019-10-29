// FILE: Sequence.cpp
// CLASS IMPLEMENTED: sequence (see sequence.h for documentation)
// INVARIANT for the sequence ADT:
//   1. The number of items in the sequence is in the member variable
//      used;
//   2. The actual items of the sequence are stored in a partially
//      filled array. The array is a dynamic array, pointed to by
//      the member variable data. For an empty sequence, we do not
//      care what is stored in any of data; for a non-empty sequence
//      the items in the sequence are stored in data[0] through
//      data[used-1], and we don't care what's in the rest of data.
//   3. The size of the dynamic array is in the member variable
//      capacity.
//   4. The index of the current item is in the member variable
//      current_index. If there is no valid current item, then
//      current_index will be set to the same number as used.
//      NOTE: Setting current_index to be the same as used to
//            indicate "no current item exists" is a good choice
//            for at least the following reasons:
//            (a) For a non-empty sequence, used is non-zero and
//                a current_index equal to used indexes an element
//                that is (just) outside the valid range. This
//                gives us a simple and useful way to indicate
//                whether the sequence has a current item or not:
//                a current_index in the valid range indicates
//                that there's a current item, and a current_index
//                outside the valid range indicates otherwise.
//            (b) The rule remains applicable for an empty sequence,
//                where used is zero: there can't be any current
//                item in an empty sequence, so we set current_index
//                to zero (= used), which is (sort of just) outside
//                the valid range (no index is valid in this case).
//            (c) It simplifies the logic for implementing the
//                advance function: when the precondition is met
//                (sequence has a current item), simply incrementing
//                the current_index takes care of fulfilling the
//                postcondition for the function for both of the two
//                possible scenarios (current item is and is not the
//                last item in the sequence).

#include <cassert>
#include "Sequence.h"
#include <iostream>
using namespace std;

namespace CS3358_SSII2019
{
   // CONSTRUCTORS and DESTRUCTOR
   sequence::sequence(size_type initial_capacity)
   {
	if (initial_capacity > 0){
		capacity = DEFAULT_CAPACITY;
		used = 0;
		data = new value_type(capacity);
		current_index = 0;
	}
   }

   sequence::sequence(const sequence& source)
   : capacity(source.capacity), used(source.used)
   {
      size_type i;

      data = new value_type[capacity];

      for( i = 0; i < used; ++i)
   	   data[i] = source.data[i];
   }

   sequence::~sequence()
   {
      delete [] data;
      
   }

   // MODIFICATION MEMBER FUNCTIONS
   void sequence::resize(size_type new_capacity)
   {
       size_type i;

       if (new_capacity < used)
           new_capacity = used;
       if (new_capacity < 1)
          new_capacity = 1;

       capacity = new_capacity;
       char * newData = new char[capacity];

       for ( i = 0; i < used; ++i)
          newData[i] = data[i];

       delete [] data;
       
       if (new_capacity < 0)
       {
    	   new_capacity = 1;
    	   if (new_capacity < used)
    	       new_capacity = used;
       }
       else
    	   data[used] = data[new_capacity];
   }

   void sequence::start()
   {
      data[0] = data[current_index];
   }

   void sequence::advance()
   {
      if(!is_item())
    	  return;
      if(current_index == used)
      {
    	  current_index = -1;
    	  return;
      }
      current_index++;
   }

   void sequence::insert(const value_type& entry)
   {
       size_type i;

       if(used +1 > capacity)
    	   resize((capacity *1.5) + 1);

       if(!is_item())
    	   current_index = 0;
       for (i = used; i > current_index; --i)
	       data[i] = data[i-1];
	   data[current_index] = entry;
	   ++used;
   }

   void sequence::attach(const value_type& entry)
   {
	  size_type i;

      if (!(size() < DEFAULT_CAPACITY))
    	  return;
      if(used == 0)
      {
         data[used] = entry;
         used++;
         return;
      }
      if (current_index != -1)
      {
    	  for (i = used; i > current_index +1; i--)
    	      data[i] = data[i - 1];
      }
      data[i] = entry;
      used++;
      current_index++;
   }

   void sequence::remove_current()
   {
      size_type i;

       if(!is_item())
    	   return;
       for(i = current_index; i < used -3; i++)
    	   data[i] = data[i+1];
       if(used-- ==1)
    	   current_index = -1;
   }

   sequence& sequence::operator=(const sequence& source)
   {
       size_type i;

       if( this != &source )
       {
          size_type* newData = new size_type[source.capacity];

	  for( i = 0; i < source.used; ++i )
	     newData[i] = source.data[i];

	  delete [] data;
	  capacity = source.capacity;
	  used = source.used;
	}
	return *this;
   }

   // CONSTANT MEMBER FUNCTIONS
   sequence::size_type sequence::size() const
   {
      return used;
   }

   bool sequence::is_item() const
   {
      if(current_index == used)
          return false;
      return true;
   }

   sequence::value_type sequence::current() const
   {
       if(!is_item())
    	   return 0;
       return data[current_index];
   }
}

