#include "slist.h"
#include <iostream>

using namespace std;

/* inserts node at the end of the list */
void LinkedList::insert(Node *data) {
  Node *next = new Node(*data);
  if (head == NULL) {
    head = next;
    return;
  }

  Node *temp = head;

  while (temp->next != NULL) {
    temp = temp->next;
  }

  temp->next = next;
}

/* prints out the size of the linkedlist */
void LinkedList::size() {
  int count = 0;
  Node *temp = head;

  while (temp->next != NULL) {
    count++;
    temp = temp->next;
  }

  cout << count << endl;
}

void LinkedList::freeList(struct Node *head) {
  Node *tmp;

  while (head != NULL) {
    tmp = head;
    head = head->next;
    delete tmp;
  }
}

void LinkedList::printList(Node *head) {
  while (head) {
    if (head->data.distance < 100) {
      cout << head->data.name << " " << head->data.distance << " miles from ABA"
           << endl;
    }
    // cout << head->data.name << " " << head->data.distance << " " <<
    // head->data.latitude << " " << head->data.longitude<< endl;
    head = head->next;
  }
}
