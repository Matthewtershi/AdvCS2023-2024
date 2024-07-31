/*
 * Binary Search Tree class
 * Do not alter the display() function, this will break the Repl.it
 * tests
 */

#include "BSTree.h"
#include <cstdlib>
#include <iostream>

using namespace std;

/*
 * Find Element in the Tree
 * find a node by item_key and provide an updated parent node
 *   pointer and location node pointer
 */

void BST::find(int item_key, node **prnt, node **loc) {
  node *ptr, *ptrsave;
  if (root == NULL) {
    *loc = NULL;
    *prnt = NULL;
    return;
  }
  if (item_key == root->key_value) {
    *loc = root;
    *prnt = NULL;
    return;
  }
  if (item_key < root->key_value)
    ptr = root->p_left;
  else
    ptr = root->p_right;
  ptrsave = root;
  while (ptr != NULL) {
    if (item_key == ptr->key_value) {
      *loc = ptr;
      *prnt = ptrsave;
      return;
    }
    ptrsave = ptr;
    if (item_key < ptr->key_value)
      ptr = ptr->p_left;
    else
      ptr = ptr->p_right;
  }
  *loc = NULL;
  *prnt = ptrsave;
}

/*
 * Inserting Element into the Tree
 */
void BST::insert(node *tree, node *newnode) {
  // if (we are at root)
  if (!tree) {
    root = newnode;
    // Just create a single node for root to point to,
    //    with all the data in it.
    return;
  }
  // if (there is already a node with our key value)
  if (tree->key_value == newnode->key_value) {
    // Just return
    return;
  }
  // if (the new node is less than the current node)
  if (newnode->key_value < tree->key_value) {
    // if (see if something is already a child on the left)
    if (tree->p_left != NULL) {
      // if so, the recurse insert at this subtree
      insert(tree->p_left, newnode);
    } else {
      // otherwise the new node goes here as a leaf (ie no children)
      tree->p_left = newnode;
      return;
    }
  } else {// it must be to the right 
    // if (is there already a child on right?)
    if (tree->p_right != NULL) {
      insert(tree->p_right, newnode);
    } else {
      tree->p_right = newnode;
      return;
    }
  }
}

/*
 * Delete Element from the tree
 */
void BST::remove(int item) {
  node *parent, *location;
  if (root == NULL) {
    cout << "Tree empty" << endl;
    return;
  }
  find(item, &parent, &location);
  if (location == NULL) {
    cout << "Item not present in tree" << endl;
    return;
  }
  // if (there is no child on left or right)
  if (location->p_left == NULL && location->p_right == NULL) {
    case_0(parent, location);
  }
  // if (there is one child on left only)
  if (location->p_left != NULL && location->p_right == NULL) {
    case_1(parent, location);
  }
  // if (there is one child on right only)
  if (location->p_left == NULL && location->p_right != NULL) {
    case_1(parent, location);
  }
  // if (there are childred on left and right)
  if (location->p_left != NULL && location->p_right != NULL) {
    case_2(parent, location);
  }

  free(location);
}

/*
 * Case 0
 * the node is simply removed no other updates necessary.
 */
void BST::case_0(node *prnt, node *loc) {
  if (prnt->p_left == loc) {
    prnt->p_left = NULL;
  } else {
    prnt->p_right = NULL;
  }
}

/*
 * Case 1
 * We have only one child so promote the child and replace the target
 * node
 */
void BST::case_1(node *prnt, node *loc) {
  node *child;
  if (loc->p_left) {
    child = loc->p_left;
  } else {
    child = loc->p_right;
  }

  if (prnt->p_left == loc) {
    prnt->p_left = child;
  } else {
    prnt->p_right = child;
  }
}

/*
 * Case case_2
 * We have to find and promote a successor or predecessor
 */
void BST::case_2(node *prnt, node *loc) {
  // temporary pointers for node we are manipulating
  node *successor;
  node *succprnt;
  succprnt = loc;
  // Find successor: Step to the right child
  successor = loc->p_right;
  // Find the min of the subtree on parent's right
  while (successor->p_left) {
    succprnt = successor;
    successor = successor->p_left;
  }
  if (successor->p_right == NULL && successor->p_left == NULL) {
    case_0(succprnt, successor);
  } else {
    case_1(succprnt, successor);
  }
  if (prnt == NULL) {
    root = successor;
  } else {
    if (loc == prnt->p_left) {
      prnt->p_left = successor;
    } else {
      prnt->p_right = successor;
    }
  }
  successor->p_left = loc->p_left;
  successor->p_right = loc->p_right;
  
  // if (found node has no children)
  //    // Replace the target node with the successor node
  //  else {
  //      // Temporarily remove the successor node by replacing it with
  //      // its right child, we will replace the node we are removing
  //      // with the successor we just removed.
  //  }
  //  //if (we are at root)
  //  {
  //      //then update root
  //  }
  //  else
  //  {
  //      // Insert the successor node where the target node we
  //      //   are removing is located
  //  }
  //  then update the successor child pointers to reflect the old
  //      target's child pointers.
}

/*
 * Display Tree Structure
 */
void BST::display(node *ptr, int level) {
  int i;
  if (ptr != NULL) {
    display(ptr->p_right, level + 1);
    cout << endl;
    if (ptr == root)
      cout << "Root->:  ";
    else {
      for (i = 0; i < level; i++)
        cout << "       ";
    }
    cout << ptr->key_value;
    display(ptr->p_left, level + 1);
  }
}
