#include <string>

using namespace std;

class Airport {
public:
  string code;
  string name;
  string type;
  double latitude;
  double longitude;
  float distance;

  Airport(string c, string n, string t, double lat, double lon) {
    code = c;
    name = n;
    type = t;
    latitude = lat;
    longitude = lon;
  }
};

class Node {

  // Constructor
  public:
    Airport data;
    Node *next;
    
  Node(Airport d) : data(d) { this->next = NULL; }
};

class LinkedList {
public:
  Node *head;
  LinkedList() { head = NULL; }

  /* inserts node at the end of the list */
  void insert(Node *data);
  /* prints out the size of the linkedlist */
  void size();
  void freeList(struct Node *head);
  void printList(Node *head);
};
