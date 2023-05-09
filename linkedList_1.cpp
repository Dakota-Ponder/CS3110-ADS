//
// This program builds a list of integer values
// by adding new nodes at the end of the list
//

#include <iostream>
using namespace std;

typedef int ListItemType;

struct Node
{
  ListItemType data;
  Node *next;
};

typedef Node *NodePtr;
void BuildList(NodePtr &head);
void PrintList(NodePtr head);

int main()
{
  int value;
  NodePtr head = NULL; // head pointer that is initialized to NULL
  NodePtr cur; // cur pointer

  BuildList(head);

  PrintList(head);

  // free memory space
  while(head != NULL)
  {
    cout << "freed a node" << endl;
    cur = head; // cur is pointing to where head is pointing
    head = head->next; // head points to the next node
    delete cur; // delete node
  }

  return 0;
}

void BuildList(NodePtr &head)
{
  int value;
  NodePtr cur;
  NodePtr tail; // another pointer to point to the end

  while(cin >> value)
  {
    cur = new Node;
    if(cur != NULL)
    {
      cur->data = value; // value is assigned to the node
      cur->next = NULL; // NULL is assigned to next
    }

    if(head == NULL)
    {
      head = cur; // head node points to where cur is pointing
      tail = cur; // tail is pointing to where cur is pointing
    }
    else
    {
      tail->next = cur;
      tail = tail->next;
    }
  }
}

void PrintList(NodePtr head)
{
  NodePtr cur;
  // print the list
  cur = head;
  while(cur != NULL)
  {
    cout << cur->data << endl;
    cur = cur->next;
  }
}