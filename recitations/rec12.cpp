/*
  rec12 / Linked List Copy Control
  Jia Sen Wu / jw3675
  CS1124
  Polytechnic University
*/

#include <cstdlib>
#include <iostream>
using namespace std;

struct Node {
  Node(int data = 0, Node* link = NULL) : data(data), link(link) {}
  int data;
  Node* link;
};

class Sequence {
public:
  Sequence() : head(NULL), pos(NULL) {}
  ~Sequence() {
    clear();
  }
  Sequence( const Sequence& copy ) {
    Node* temp = copy.head;
    Node* tempos;
    head = new Node( temp->data );
    pos = head;
    temp = temp->link;
    while( temp != NULL ) {
      pos->link = new Node( temp->data );
      pos = pos->link;
      if( copy.pos == temp ) {
	tempos = temp;
      }
      temp = temp->link;
    }
    pos = tempos;
  }
  Sequence& operator=( const Sequence copy ) {
    if( this != &copy ) {
      clear();
      Node* temp = copy.head;
      Node* tempos;
      head = new Node( temp->data );
      pos = head;
      temp = temp->link;
      while( temp != NULL ) {
	pos->link = new Node( temp->data );
	pos = pos->link;
	if( copy.pos == temp ) {
	  tempos = temp;
	}
	temp = temp->link;
      }
      pos = tempos;
    }
  }
  void reset() {
    pos = head;
  }
  void add( int data ) {
    Node* next = new Node( data );
    if( head == NULL ) {
      head = next;
      pos = next;
    } else if( pos != NULL ) {
      Node* temp = pos->link;
      pos->link = next;
      next->link = temp;
      pos = pos->link;
    } else {
      next->link = head;
      head = next;
    }
  }
  void remove() {
    if( valid() ) {
      Node* left = head;
      Node* right = pos->link;
      while( left != NULL ) {
	if( left->link == pos ) {
	  break;
	} else {
	  left = left->link;
	}
      }
      delete pos;
      left->link = right;
      pos = right;
    }
  }
  int data() const {
    if( valid() ) {
      return pos->data;
    }
  }
  void next() {
    if( valid() ) {
      pos = pos->link;
    }
  }
  bool valid() const {
    return pos != NULL;
  }
  void clear() {
    while( head ) {
      Node* temp = head->link;
      delete head;
      head = temp;
    }
    pos = NULL;
  }
  void display( ostream& os = cout, char sep = ' ' ) const {
    Node* temp = head;
    while( temp != NULL ) {
      os << temp->data << sep;
      temp = temp->link;
    }
    os << endl;
  }
private:
  Node* head;
  Node* pos;
};

int main() {
  Sequence s;
  Sequence u;
  for (int i = 0; i < 6; ++i) s.add(i);
  s.display();
  cout << "==========\n";
  s.reset();
  for (int i = 0; i < 3; ++i) s.next();
  s.add(42);
  s.display();
  s.reset();
  cout << "=CopyOper=\n";
  Sequence t(s);
  t.display();
  t.reset();
  cout << "=AssnOper=\n";
  u = s;
  u.display();
  u.reset();
  cout << "==========\n";
  for (int i = 0; i < 2; ++i) s.next();
  s.remove();
  s.display();
  cout << "=CopyList=\n";
  for (int i = 0; i < 2; ++i) t.next();
  t.remove();
  t.display();
  cout << "=AssnList=\n";
  for (int i = 0; i < 2; ++i) u.next();
  u.remove();
  u.display();
  cout << "==========\n";
  s.clear();
  s.display();
  cout << "==========\n";
}
