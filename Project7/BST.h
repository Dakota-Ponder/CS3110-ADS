#ifndef BST_H
#define BST_H

#include "wordEntry.h"
#include <iostream>
#include <string>
using namespace std;

typedef string keyType;
typedef TextEntry treeItemType;
typedef void (*functionType)(treeItemType &AnItem);

struct Node;
typedef Node *nodePtr; // pointer to node

struct Node {
  treeItemType Item;
  nodePtr LChildPtr, RChildPtr;

  // constructor:
  Node(const treeItemType &NodeItem, nodePtr L, nodePtr R);
}; // end struct

class BinarySearchTree {
public:
  // constructors and destructor:
  BinarySearchTree();                             // default constructor
  BinarySearchTree(const BinarySearchTree &Tree); // copy constructor
  ~BinarySearchTree();                            // destructor

  // binary search tree operations:
  // Precondition for all methods: No two items in a binary
  // search tree have the same search key.

  bool SearchTreeIsEmpty() const;
  // Determines whether a binary search tree is empty.
  // Postcondition: Returns true if the tree is empty;
  // otherwise returns false.

  void SearchTreeInsert(const treeItemType &NewItem, bool &Success);
  // Inserts an item into a binary search tree.
  // Precondition: The item to be inserted into the tree
  // is NewItem.
  // Postcondition: If the insertion was successful,
  // NewItem is in its proper order in the tree and
  // Success is true. Otherwise, the tree is unchanged and
  // Success is false.

  void SearchTreeDelete(keyType SearchKey, bool &Success);
  // Deletes an item with a given search key from a binary
  // search tree.
  // Precondition: SearchKey is the search key of the item
  // to be deleted.
  // Postcondition: If the item whose search key equals
  // SearchKey existed in the tree, the item is deleted and
  // Success is true. Otherwise, the tree is unchanged and
  // Success is false.

  void SearchTreeRetrieve(keyType SearchKey, treeItemType &TreeItem,
                          bool &Success) const;
  // Retrieves an item with a given search key from a
  // binary search tree.
  // Precondition: SearchKey is the search key of the item
  // to be retrieved.
  // Postcondition: If the retrieval was successful,
  // TreeItem contains the retrieved item and Success is
  // true. If no such item exists, TreeItem and the tree
  // are unchanged and Success is false.

  void PreorderTraverse(functionType Visit);
  // Traverses a binary search tree in preorder,
  // calling function Visit once for each item.
  // Precondition: The function represented by Visit
  // exists outside of the class implementation.
  // Postcondition: Visit's action occurred once for each
  // item in the tree.
  // Note: Visit can alter the tree.

  void InorderTraverse(functionType Visit);
  // Traverses a binary search tree in sorted order,
  // calling function Visit once for each item.

  void PostorderTraverse(functionType Visit);
  // Traverses a binary search tree in postorder,
  // calling function Visit once for each item.

  // overloaded operator:
  BinarySearchTree &operator=(const BinarySearchTree &Rhs);

private:
  void InsertItem(nodePtr &TreePtr, const treeItemType &NewItem, bool &Success);
  // Recursively inserts an item into a binary search tree.
  // Precondition: TreePtr points to a binary search tree,
  // NewItem is the item to be inserted.
  // Postcondition: Same as SearchTreeInsert.

  void DeleteItem(nodePtr &TreePtr, keyType SearchKey, bool &Success);
  // Recursively deletes an item from a binary search tree.
  // Precondition: TreePtr points to a binary search tree,
  // SearchKey is the search key of the item to be deleted.
  // Postcondition: Same as SearchTreeDelete.

  void DeleteNodeItem(nodePtr &NodePtr);
  // Deletes the item in the root of a given tree.
  // Precondition: RootPtr points to the root of a
  // binary search tree; RootPtr != NULL.
  // Postcondition: The item in the root of the given
  // tree is deleted.

  void ProcessLeftmostChild(nodePtr &NodePtr, treeItemType &TreeItem);
  // Retrieves and deletes the leftmost descendant of a
  // given node.
  // Precondition: NodePtr points to a node in a binary
  // search tree; NodePtr != NULL.
  // Postcondition: TreeItem contains the item in the
  // leftmost descendant of the node to which NodePtr
  // points. The leftmost descendant of NodePtr is
  // deleted.

  void RetrieveItem(nodePtr TreePtr, keyType SearchKey, treeItemType &TreeItem,
                    bool &Success) const;
  // Recursively retrieves an item from a binary search
  // tree.
  // Precondition: TreePtr points to a binary search tree,
  // SearchKey is the search key of the item to be
  // retrieved.
  // Postcondition: Same as SearchTreeRetrieve.

  void CopyTree(nodePtr TreePtr, nodePtr &NewTreePtr) const;
  void DestroyTree(nodePtr &TreePtr);

  void Preorder(nodePtr TreePtr, functionType Visit);
  void Inorder(nodePtr TreePtr, functionType Visit);
  void Postorder(nodePtr TreePtr, functionType Visit);

  nodePtr RootPtr() const;
  void SetRootPtr(nodePtr NewRoot);

  void GetChildPtrs(nodePtr NodePtr, nodePtr &LChildPtr,
                    nodePtr &RChildPtr) const;
  void SetChildPtrs(nodePtr NodePtr, nodePtr LChildPtr, nodePtr RChildPtr);

  nodePtr Root; // pointer to root of tree
};              // end class
// End of header file.

#endif