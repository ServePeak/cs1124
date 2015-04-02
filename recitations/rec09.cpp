/*
  Recitation 09
  CS1124
 
  Focus: Copy Control.  Uses dynamic array of pointers.
*/

#include <string>
#include <iostream>
using namespace std;

class Position {
public:
  Position(const string& aTitle, double aSalary)
    : title(aTitle), salary(aSalary) {}
  string getTitle() const {return title;}
  double getSalary() const {return salary;}
  void changeSalaryTo(double d) {salary = d;}
private:
  string title;
  double salary;
}; // class Position

class Entry {
public:
  Entry(const string& aName, unsigned aRoom, unsigned aPhone,
	Position& aPosition) 
    : name(aName), room(aRoom), phone(aPhone), pos(&aPosition) {
  }
  friend ostream& operator<<( ostream& os, const Entry& e ) {
    os << e.name << ' ' << e.room << ' ' << e.phone;
    return os;
  } // operator <<
  string getName() const {
    return name;
  }
private:
  string name;
  unsigned room;
  unsigned phone;
  Position* pos;
}; // class Entry

class Directory {
public:
  Directory()
    : capacity(2), size(0), entries(new Entry*[2] )
  {
    // Should we do this?  What do you think?
    for (size_t i = 0; i < capacity; i++) {
      entries[i] = nullptr;
    } // for
  } // Directory()
  
  Directory( const Directory& d ) {
    size = d.size;
    capacity = d.capacity;
    entries = new Entry*[ capacity ];
    for( size_t i = 0; i < size; i++ ) {
      //cout << *d.entries[i] << endl;
      entries[i] = new Entry( *d.entries[i] );
    }
  }

  ~Directory() {
    for( size_t i = 0; i < size; i++ ) {
      delete entries[i];
    }
    delete [] entries;
  }

  Directory& operator=( const Directory& right ) {
    if( this != &right ) {
      for( size_t i = 0; i < size; i++ ) {
	delete entries[i];
      }
      delete [] entries;
      size = right.size;
      capacity = right.capacity;
      entries = new Entry*[capacity];
      for( size_t i = 0; i < size; i++ ) {
	entries[i] = new Entry(*right.entries[i]);
      }
    }
  }

  unsigned operator[]( const string& name ) const {
    for( size_t i = 0; i < size; i++ ) {
      if( entries[i]->getName() == name ) {
	cout << *entries[i] << endl;
      } else {
	cout << "Person not in entries" << endl;
      }
    }
  }
    
  friend ostream& operator<<( ostream& os, const Directory d ) {
    for( size_t i = 0; i < d.size; i++ ) {
      os << *d.entries[i] << endl;
    }
    return os;
  }
  
  void add(const string& name, unsigned room, unsigned ph, Position& pos) {
    if( size == capacity )	{
      Entry** temp = entries;
      capacity *= 2;
      entries = new Entry*[ capacity ];
      for( size_t i = 0; i < size; i++ ) {
	entries[i] = temp[i];
      }
      delete [] temp;
    } // if
    entries[size] = new Entry(name, room, ph, pos);
    ++size;
  } // add
private:	
  Entry** entries;
  size_t size;
  size_t capacity;
}; // class Directory

void doNothing(Directory dir) { cout << dir << endl; }

int main() {
  
  // Model as if there are these four kinds 
  // of position in the problem:
  Position boss("Boss", 3141.59);
  Position pointyHair("Pointy Hair", 271.83);
  Position techie("Techie", 14142.13);
  Position peon("Peonissimo", 34.79);
  
  // Create a Directory
  Directory d;
  d.add("Marilyn", 123, 4567, boss);
  cout << d << endl;
  
  Directory d2 = d;	// What function is being used??
  d2.add("Gallagher", 111, 2222, techie);
  d2.add("Carmack", 314, 1592, techie);
  cout << d2 << endl;
  
  cout << "Calling doNothing\n";
  doNothing(d2);
  cout << "Back from doNothing\n";
  
  Directory d3;
  d3 = d2;
  
  //d["Marilyn"];
} // main
