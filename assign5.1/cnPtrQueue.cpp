#include "cnPtrQueue.h"
#include <cassert>
using namespace std;

namespace CS3358_SSII2019_A5P1
{
   cnPtrQueue::cnPtrQueue()
   {
        numItems =0;
   }  

   void cnPtrQueue::push( CNode* cnPtr )
   {
      inStack.push( cnPtr );
      ++numItems;
   }

   void cnPtrQueue::pop( )
   {
      assert( !inStack.empty() || !outStack.empty() );
      if( outStack.empty( ))
         while( !inStack.empty( ) )
         {
            outStack.push(inStack.top() );
            inStack.pop( );
         }
      outStack.pop( );
      --numItems;
   }

   CNode* cnPtrQueue::front( )
   {
      assert( !inStack.empty( ) || !outStack.empty( ) );
      if( outStack.empty( ) )
         while( !inStack.empty( ) )
         {
            outStack.push( inStack.top( ) );
            inStack.pop( );
         }
      return outStack.top( );
   }

   bool cnPtrQueue::empty() const
   {
	if(outStack.empty() && inStack.empty()){
		return true;
	}	
	return false;	
      
   }

   cnPtrQueue::size_type cnPtrQueue::size( ) const
   {
      return numItems;
   }
}
