#ifndef BST_CPP
#define BST_CPP

#include "BST.h"
#include <stdlib.h>
using namespace std;

//
Node::Node(const treeItemType &NodeItem, nodePtr L, nodePtr R)
    : Item(NodeItem), LChildPtr(L), RChildPtr(R) {} // end constructor

//
BinarySearchTree::BinarySearchTree() : Root(NULL) {} // end default constructor

BinarySearchTree::BinarySearchTree(const BinarySearchTree &Tree) {
  CopyTree(Tree.Root, Root);
} // end copy constructor

BinarySearchTree::~BinarySearchTree() { DestroyTree(Root); } // end destructor

// check if the tree is empty
bool BinarySearchTree::SearchTreeIsEmpty() const {
  return bool(Root == NULL);
} // end SearchTreeIsEmpty

void BinarySearchTree::SearchTreeInsert(const treeItemType &NewItem,
                                        bool &Success) {
  InsertItem(Root, NewItem, Success);
} // end SearchTreeInsert

void BinarySearchTree::SearchTreeDelete(keyType SearchKey, bool &Success) {
  DeleteItem(Root, SearchKey, Success);
} // end SearchTreeDelete

void BinarySearchTree::SearchTreeRetrieve(keyType SearchKey,
                                          treeItemType &TreeItem,
                                          bool &Success) const {
  RetrieveItem(Root, SearchKey, TreeItem, Success);
} // end SearchTreeRetrieve

void BinarySearchTree::PreorderTraverse(functionType Visit) {
  Preorder(Root, Visit);
} // end PreorderTraverse

void BinarySearchTree::InorderTraverse(functionType Visit) {
  Inorder(Root, Visit);
} // end InorderTraverse

void BinarySearchTree::PostorderTraverse(functionType Visit) {
  Postorder(Root, Visit);
} // end PostorderTraverse

// function to insert an item into the tree in its proper order
void BinarySearchTree::InsertItem(nodePtr &TreePtr, const treeItemType &NewItem,
                                  bool &Success) {
  if (TreePtr == NULL) { // position of insertion found; insert after leaf

    // create a new node
    TreePtr = new Node(NewItem, NULL, NULL);

    // was allocation successful?
    Success = bool(TreePtr != NULL);
  }

  // else search for the insertion position
  else if (NewItem.Key() < TreePtr->Item.Key())
    // search the left subtree
    InsertItem(TreePtr->LChildPtr, NewItem, Success);

  else // search the right subtree
    InsertItem(TreePtr->RChildPtr, NewItem, Success);
} // end InsertItem

void BinarySearchTree::DeleteItem(nodePtr &TreePtr, keyType SearchKey,
                                  bool &Success)
// Calls: DeleteNodeItem.
{
  if (TreePtr == NULL)
    Success = false; // empty tree

  else if (SearchKey ==
           TreePtr->Item.Key()) { // item is in the root of some subtree
    DeleteNodeItem(TreePtr);      // delete the item
    Success = true;
  } // end if in root

  // else search for the item
  else if (SearchKey < TreePtr->Item.Key())
    // search the left subtree
    DeleteItem(TreePtr->LChildPtr, SearchKey, Success);

  else // search the right subtree
    DeleteItem(TreePtr->RChildPtr, SearchKey, Success);
} // end DeleteItem

void BinarySearchTree::DeleteNodeItem(nodePtr &NodePtr)
// Algorithm note: There are four cases to consider:
//   1. The root is a leaf.
//   2. The root has no left child.
//   3. The root has no right child.
//   4. The root has two children.
// Calls: ProcessLeftmostChild.
{
  nodePtr DelPtr;
  treeItemType ReplacementItem;

  // test for a leaf
  if ((NodePtr->LChildPtr == NULL) && (NodePtr->RChildPtr == NULL)) {
    delete NodePtr;
    NodePtr = NULL;
  } // end if leaf

  // test for no left child
  else if (NodePtr->LChildPtr == NULL) {
    DelPtr = NodePtr;
    NodePtr = NodePtr->RChildPtr;
    DelPtr->RChildPtr = NULL;
    delete DelPtr;
  } // end if no left child

  // test for no right child
  else if (NodePtr->RChildPtr == NULL) {
    DelPtr = NodePtr;
    NodePtr = NodePtr->LChildPtr;
    DelPtr->LChildPtr = NULL;
    delete DelPtr;
  } // end if no right child

  // there are two children:
  // retrieve and delete the inorder successor
  else {
    ProcessLeftmostChild(NodePtr->RChildPtr, ReplacementItem);
    NodePtr->Item = ReplacementItem;
  } // end if two children
} // end DeleteNodeItem

void BinarySearchTree::ProcessLeftmostChild(nodePtr &NodePtr,
                                       treeItemType &TreeItem) {
  if (NodePtr->LChildPtr == NULL) {
    TreeItem = NodePtr->Item;
    nodePtr DelPtr = NodePtr;
    NodePtr = NodePtr->RChildPtr;
    DelPtr->RChildPtr = NULL; //
    delete DelPtr;
  }

  else
    ProcessLeftmostChild(NodePtr->LChildPtr, TreeItem);
} // end ProcessLeftmostChild

void BinarySearchTree::RetrieveItem(nodePtr TreePtr, keyType SearchKey,
                                    treeItemType &TreeItem,
                                    bool &Success) const {
  if (TreePtr == NULL)
    Success = false; // empty tree

  else if (SearchKey ==
           TreePtr->Item.Key()) { // item is in the root of some subtree
    TreeItem = TreePtr->Item;
    Success = true;
  }

  else if (SearchKey < TreePtr->Item.Key())
    // search the left subtree
    RetrieveItem(TreePtr->LChildPtr, SearchKey, TreeItem, Success);

  else // search the right subtree
    RetrieveItem(TreePtr->RChildPtr, SearchKey, TreeItem, Success);
} // end RetrieveItem

BinarySearchTree &BinarySearchTree::operator=(const BinarySearchTree &Rhs) {
  if (this != &Rhs) {
    DestroyTree(Root);        // deallocate left-hand side
    CopyTree(Rhs.Root, Root); // copy right-hand side
  }                           // end if
  return *this;
} // end operator=

void BinarySearchTree::CopyTree(nodePtr TreePtr, nodePtr &NewTreePtr) const {
  // preorder traversal
  if (TreePtr != NULL) { // copy node
    NewTreePtr = new Node(TreePtr->Item, NULL, NULL);
    // assert(NewTreePtr != NULL);

    CopyTree(TreePtr->LChildPtr, NewTreePtr->LChildPtr);
    CopyTree(TreePtr->RChildPtr, NewTreePtr->RChildPtr);
  } // end if
  else
    NewTreePtr = NULL; // copy empty tree
} // end CopyTree

void BinarySearchTree::DestroyTree(nodePtr &TreePtr) {
  // postorder traversal
  if (TreePtr != NULL) {
    DestroyTree(TreePtr->LChildPtr);
    DestroyTree(TreePtr->RChildPtr);
    delete TreePtr;
    TreePtr = NULL;
  } // end if
} // end DestroyTree

nodePtr BinarySearchTree::RootPtr() const { return Root; } // end RootPtr

void BinarySearchTree::SetRootPtr(nodePtr NewRoot) {
  Root = NewRoot;
} // end SetRoot

void BinarySearchTree::GetChildPtrs(nodePtr NodePtr, nodePtr &LeftPtr,
                                    nodePtr &RightPtr) const {
  LeftPtr = NodePtr->LChildPtr;
  RightPtr = NodePtr->RChildPtr;
} // end GetChildPtrs

void BinarySearchTree::SetChildPtrs(nodePtr NodePtr, nodePtr LeftPtr,
                                    nodePtr RightPtr) {
  NodePtr->LChildPtr = LeftPtr;
  NodePtr->RChildPtr = RightPtr;
} // end SetChildPtrs

void BinarySearchTree::Preorder(nodePtr TreePtr, functionType Visit) {
  if (TreePtr != NULL) {
    Visit(TreePtr->Item);
    Preorder(TreePtr->LChildPtr, Visit);
    Preorder(TreePtr->RChildPtr, Visit);
  } // end if
} // end Preorder

void BinarySearchTree::Inorder(nodePtr TreePtr, functionType Visit) {
  if (TreePtr != NULL) {
    Inorder(TreePtr->LChildPtr, Visit);
    Visit(TreePtr->Item);
    Inorder(TreePtr->RChildPtr, Visit);
  } // end if
} // end Inorder

void BinarySearchTree::Postorder(nodePtr TreePtr, functionType Visit) {
  if (TreePtr != NULL) {
    Postorder(TreePtr->LChildPtr, Visit);
    Postorder(TreePtr->RChildPtr, Visit);
    Visit(TreePtr->Item);
  } // end if
} // end Postorder
// End of implementation file.

#endif