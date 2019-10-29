
#include "btNode.h"

void dumpToArrayInOrder(btNode* bst_root, int* dumpArray)
{
   if (bst_root == 0) return;
   int dumpIndex = 0;
   dumpToArrayInOrderAux(bst_root, dumpArray, dumpIndex);
}

void dumpToArrayInOrderAux(btNode* bst_root, int* dumpArray, int& dumpIndex)
{
   if (bst_root == 0) return;
   dumpToArrayInOrderAux(bst_root->left, dumpArray, dumpIndex);
   dumpArray[dumpIndex++] = bst_root->data;
   dumpToArrayInOrderAux(bst_root->right, dumpArray, dumpIndex);
}

void tree_clear(btNode*& root)
{
   if (root == 0) return;
   tree_clear(root->left);
   tree_clear(root->right);
   delete root;
   root = 0;
}

int bst_size(btNode* bst_root)
{
   if (bst_root == 0) return 0;
   return 1 + bst_size(bst_root->left) + bst_size(bst_root->right);
}

// write definition for bst_insert here
bool bst_insert(btNode*& bst_root, int newInt)
{
	if(bst_root == 0)
		return false;

	btNode* cursor = bst_root;
	bool finished = false;

	while(!finished)
	{
		if(newInt < cursor->data)
		{
			if(cursor->left ==0)
			{
				cursor->left = new btNode;
				cursor->left->data = newInt;
				cursor->left->left = 0;
				cursor->left->right = 0;
				finished = true;
			}
			else
				cursor= cursor->left;
		}
		else if (newInt > cursor->data)
		{
			if(cursor->right == 0)
			{
				cursor->right = new btNode;
				cursor->right->data = newInt;
				cursor->right->left = 0;
				cursor->right->right = 0;
				finished = true;
			}
			else 
				cursor = cursor->right;
		}
		else 
			return false;			
	}
}

// write definition for bst_remove here
bool bst_remove(btNode* bst_root, int remInt)
{
   bool found = false;

   if(bst_root == 0)
      return found;

   btNode* remPtr = 0;

   if(remPtr != bst_root)
   {
      if(remInt > bst_root->data)
         if(bst_root->right != 0)
           return found;            
//found = bst_remove(bst_root->right, remInt);
      else
         if(bst_root->left != 0)
           return found;            
//found = bst_remove(bst_root->left, remInt);
   }
   else
   {
      found = true;
      if(bst_root->left != 0 && bst_root->right != 0)
         bst_remove_max(bst_root->left, bst_root->data);
      else
      {
         remPtr = bst_root;

         if(bst_root->left == 0 && bst_root->right == 0)
            bst_root = 0;
         else if(bst_root->right == 0 && bst_root->left != 0)
            bst_root = bst_root->left;
         else if (bst_root->left == 0 && bst_root->right != 0)
            bst_root= bst_root->right;

         delete remPtr;
      }
   }
   return found;
}
// write definition for bst_remove_max here
void bst_remove_max(btNode*& bst_root, int& data)
{

   btNode* curPtr = 0;
   curPtr = bst_root;
   btNode* remPtr = 0;

   if(curPtr->right == 0)
   {
      data = curPtr->data;
      remPtr = curPtr;
      bst_root= bst_root->left;
      delete remPtr;
   }
   else
      bst_remove_max( curPtr->right, data);
}
