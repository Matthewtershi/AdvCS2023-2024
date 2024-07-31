/*
 * LaQueue
 * 
 * 
 * This is part of a series of labs for the Liberal Arts and Science Academy.
 * The series of labs provides a mockup of an POSIX Operating System
 * referred to as LA(SA)nix or LAnix.
 *  
 * (c) copyright 2018, James Shockey - all rights reserved
 * 
 * */

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include "PQueue.h"



/*
 * Class Priority Queue
 */

		
/*
* Insert into Priority Queue
*/
void PQueue::push(void *item, int priority)
{
  node* newNode = new node();
  newNode->data = item;
  newNode->priority = priority;
  
  if (front == nullptr) {
    newNode->link = front;
    front = newNode;
  }
  
  else {
    node* curr = newNode;
    curr = front;
    while (curr->link != nullptr && curr->link->priority > priority) {
      curr = curr->link;
    }

    newNode->link = curr->link;
    curr->link = newNode;
  }
	/* Your code here */
}

/*
 * Delete from Priority Queue
 */
void* PQueue::top()
{
  if (front) {
    return front->data;
  } else {
    return nullptr;
  }
	/* Your code here */
}
/*
 * Delete from Priority Queue
 */
void PQueue::pop()
{
  if (front) {
    node* temp = front;
    front = front->link;
    delete(temp);
  }
}

/*
 * Print Priority Queue
 */
void PQueue::display()
{
	/* Your code here */
	
	/* Use the following out command for the data */
  node* ptr = front;
  do {
    std::cout<<ptr->priority<<" "<<(char*)ptr->data<<std::endl;
    //ptr = ptr->link;
  } while (ptr->link != nullptr);

}
	