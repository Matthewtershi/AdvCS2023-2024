//*****************************************************************
//  LinkedList.cpp
//  HashTable

//
//  This header file contains the Linked List class declaration.
//  Hash Table array elements consist of Linked List objects.
//*****************************************************************

#include "LinkedList.h"

// Constructs the empty linked list object.
// Creates the head node and sets length to zero.
LinkedList::LinkedList() {
  head = NULL;
  length = 0;
}

// Inserts an item at the end of the list.
void LinkedList::insert(Element *newElement) {
  if (head == NULL) {
    head = newElement;
    length++;
    return;
  }

  Element *temp = head;

  while (temp->next != NULL) {
    temp = temp->next;
  }

  temp->next = newElement;
  length++;
}

// Removes an item from the list by item key.
// Returns true if the operation is successful.
bool LinkedList::remove(string Key) {
  // * * * * * * * * * * *
  // Your code goes here
  // * * * * * * * * * * *
  Element *temp = head;
  Element *prev = nullptr;

  while (temp != nullptr) {
    if (temp->key == Key) {

      if (temp == head) {
        head = temp->next;
        delete temp;
      }

      else {
        prev->next = temp->next;
        delete temp;
      }

      length--;
      return true;
    }

    prev = temp;
    temp = temp->next;
  }
  return false;
}

// Searches for an item by its key.
// Returns a reference to first match.
// Returns a NULL pointer if no match is found.
Element *LinkedList::get(string Key) {
  // * * * * * * * * * * *
  // Your code goes here
  // * * * * * * * * * * *
  Element *temp = head;

  while (temp != nullptr) {
    if (temp->key == Key) {
      return temp;
    }

    temp = temp->next;
  }
  return nullptr;
}

// Displays list contents to the console window.
void LinkedList::printList() {
  if (length == 0) {
    cout << "\n{ }\n";
    return;
  }
  Element *p = head;
  Element *q = head;
  cout << "\n{ ";
  while (q) {
    p = q;
    // if (p != head)
    if (p != nullptr) {
      cout << p->key;
      if (p->next)
        cout << ", ";
      else
        cout << " ";
    }
    q = p->next;
  }
  cout << "}\n";
}

// Returns the length of the list.
int LinkedList::getLength() { return length; }

// De-allocates list memory when the program terminates.
LinkedList::~LinkedList() {
  // * * * * * * * * * * *
  // Your code goes here
  // * * * * * * * * * * *
  Element *tmp;

  while (head != NULL) {
    tmp = head;
    head = head->next;
    length = 0;
    delete tmp;
  }
}

//*****************************************************************
// End of File
//*****************************************************************