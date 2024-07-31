#include "RBtree.h"

using namespace std;

RBtree::RBtree() {
	NIL = new Node;
	NIL->color = BLACK;
	NIL->left = nullptr;
	NIL->right = nullptr;
	root = NIL;
}

RBtree::~RBtree()
{
}



Node* RBtree::searchTreeHelper(Node* node, int key) {
	if (node == NIL || key == node->key) {
		return node;
	}

	if (key < node->key) {
		return searchTreeHelper(node->left, key);
	} 
	return searchTreeHelper(node->right, key);
}

// fix-up remove operation
void RBtree::fixRemove(Node* x) {
	Node* s;
	while (x != root && x->color == BLACK) {
		if (x == x->parent->left) {
			s = x->parent->right;
			if (s->color == RED) {
				s->color = BLACK;
				x->parent->color = RED;
				leftRotate(x->parent);
				s = x->parent->right;
			}

			if (s->left->color == BLACK && s->right->color == BLACK) {
				s->color = RED;
				x = x->parent;
			} else {
				if (s->right->color == BLACK) {
					s->left->color = BLACK;
					s->color = RED;
					rightRotate(s);
					s = x->parent->right;
				} 

				s->color = x->parent->color;
				x->parent->color = BLACK;
				s->right->color = BLACK;
				leftRotate(x->parent);
				x = root;
			}
		} else {
			s = x->parent->left;
			if (s->color == RED) {
				s->color = BLACK;
				x->parent->color = RED;
				rightRotate(x->parent);
				s = x->parent->left;
			}

			if (s->right->color == BLACK && s->right->color == BLACK) {
				s->color = RED;
				x = x->parent;
			} else {
				if (s->left->color == BLACK) {
					s->right->color = BLACK;
					s->color = RED;
					leftRotate(s);
					s = x->parent->left;
				} 

				s->color = x->parent->color;
				x->parent->color = BLACK;
				s->left->color = BLACK;
				rightRotate(x->parent);
				x = root;
			}
		} 
	}
	x->color = BLACK;
}


void RBtree::transplant(Node* u, Node* v){
	if (u->parent == nullptr) {
		root = v;
	} else if (u == u->parent->left){
		u->parent->left = v;
	} else {
		u->parent->right = v;
	}
	v->parent = u->parent;
}

void RBtree::remove(int key) {
	removeNodeRecursive(this->root, key);
}


void RBtree::removeNodeRecursive(Node* node, int key) {
	Node* z = NIL;
	Node *x, *y;
	while (node != NIL){
		if (node->key == key) {
			z = node;
		}

		if (node->key <= key) {
			node = node->right;
		} else {
			node = node->left;
		}
	}

	if (z == NIL) {
		cout<<"tree is empty"<<endl;
		return;
	} 

	y = z;
	int y_original_color = y->color;
	if (z->left == NIL) {
		x = z->right;
		transplant(z, z->right);
	} else if (z->right == NIL) {
		x = z->left;
		transplant(z, z->left);
	} else {
		y = minimum(z->right);
		y_original_color = y->color;
		x = y->right;
		if (y->parent == z) {
			x->parent = y;
		} else {
			transplant(y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}

		transplant(z, y);
		y->left = z->left;
		y->left->parent = y;
		y->color = z->color;
	}
	delete z;
	if (y_original_color == BLACK){
		fixRemove(x);
	}
}


void RBtree::fixInsert(Node* z){

  Node* y;

  while (z->parent->color == RED) {
    if (z->parent == z->parent->parent->left) {
      //cout << "error in fixInsert" << endl;
      y = (z->parent->parent->right != nullptr) ? z->parent->parent->right : NIL;

      if (y->color == RED) {
        z->parent->color = BLACK;
        y->color = BLACK;
        z->parent->parent->color = RED;
        z = z->parent->parent;
      }

      else {
        if (z == z->parent->right) {
          z = z->parent;
          leftRotate(z);
        }

        z->parent->color = BLACK;
        z->parent->parent->color = RED;
        rightRotate(z->parent->parent);
      }
    } 
    
    else if (z->parent == z->parent->parent->right) {
      //cout << "error in fixInsert2" << endl;
      //cout << (z->parent == z->parent->parent->left) << endl;
      y = (z->parent->parent->left != nullptr) ? z->parent->parent->left : NIL;

      if (y->color == RED) {
        z->parent->color = BLACK;
        y->color = BLACK;
        z->parent->parent->color = RED;
        z = z->parent->parent;
      }

      else {
        if (z == z->parent->left) {
          z = z->parent;
          rightRotate(z);
        }

        z->parent->color = BLACK;
        z->parent->parent->color = RED;
        leftRotate(z->parent->parent);
      }

    }
    
  }

  root->color = BLACK;
}

void RBtree::leftRotate(Node* x) {
  //cout << "leftRotate" << endl;
  Node* right = x->right;
  x->right = right->left;

  if (right->left != NIL) {
    right->left->parent = x;
  }

  right->parent = x->parent;

  if (x->parent == NIL) {
    root = right;
  } 

  else if (x == x->parent->left) {
    x->parent->left = right;
  }

  else {
    x->parent->right = right;
  }

  right->left = x;
  x->parent = right;
}


void RBtree::rightRotate(Node* x) {
  //cout << "rightRotate" << endl;
  Node* left = x->left;
  x->left = left->right;

  if (left->right != NIL) {
    left->right->parent = x;
  }

  left->parent = x->parent;

  if (x->parent == NIL) {
    root = left;
  } 

  else if (x == x->parent->right) {
    x->parent->right = left;
  }

  else {
    x->parent->left = left;
  }

  left->right = x;
  x->parent = left;
}



void RBtree::insert(int key) {
  Node* z = new Node();
  z -> key = key;
  Node* y = NIL;
  Node* x = this->root;
  //cout << "error in insert" << endl;
  while (x != NIL) {
    y = x;
    if (key < x->key) {
      x = x->left;
    } else {
      x = x->right;
    }
  }

  z->parent = y;

  if (y == NIL) {
    root = z;
  } 

  else if (key < y->key) {
    y->left = z;
  } 

  else {
    y->right = z;
  }

  z -> left = NIL;
  z -> right = NIL;
  z -> color = RED;
	fixInsert(z);
  //cout << "Insertion successful" << endl;
}






void RBtree::printTraverse(Node* root, string indent, bool last) {
  
	if (root != NIL) {
	   cout<<indent;
	   if (last) {
		  cout<<"R----";
		  indent += "     ";
	   } else {
		  cout<<"L----";
		  indent += "|    ";
	   }
		
	   string sColor = root->color?"RED":"BLACK";
	   cout<<root->key<<"("<<sColor<<")"<<endl;
	   printTraverse(root->left, indent, false);
	   printTraverse(root->right, indent, true);
	}
  
}


void RBtree::preorder() {
	RBtree::preOrderTraverse(this->root);
}

void RBtree::preOrderTraverse(Node* node) {
	if (node != NIL) {
		cout<<node->key<<" ";
		preOrderTraverse(node->left);
		preOrderTraverse(node->right);
	} 
}



void RBtree::inorder() {
	inOrderTraverse(this->root);
}
void RBtree::inOrderTraverse(Node* node) {
	if (node != NIL) {
		inOrderTraverse(node->left);
		cout<<node->key<<" ";
		inOrderTraverse(node->right);
	} 
}

void RBtree::postorder() {
	postOrderTraverse(this->root);
}

void RBtree::postOrderTraverse(Node* node) {
	if (node != NIL) {
		postOrderTraverse(node->left);
		postOrderTraverse(node->right);
		cout<<node->key<<" ";
	} 
}


Node* RBtree::searchTree(int k) {
	return searchTreeHelper(this->root, k);
}


Node* RBtree::minimum(Node* node) {
	while (node->left != NIL) {
		node = node->left;
	}
	return node;
}


Node* RBtree::maximum(Node* node) {
	while (node->right != NIL) {
		node = node->right;
	}
	return node;
}


Node* RBtree::successor(Node* x) {


	if (x->right != NIL) {
		return minimum(x->right);
	}


	Node* y = x->parent;
	while (y != NIL && x == y->right) {
		x = y;
		y = y->parent;
	}
	return y;
}

Node* RBtree::predecessor(Node* x) {


	if (x->left != NIL) {
		return maximum(x->left);
	}

	Node* y = x->parent;
	while (y != NIL && x == y->left) {
		x = y;
		y = y->parent;
	}

	return y;
}


Node* RBtree::getRoot(){
	return this->root;
}



void RBtree::prettyPrint() {
	if (root) {
		printTraverse(this->root, "", true);
	}
}


