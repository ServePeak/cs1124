/*
	rec04 - pointers
	Jia Sen Wu / jw3675
	CS1124
	Polytechnic University
*/

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
using namespace std;

struct Complex {
  double real;
  double img;
};

class PlainOldClass {  
public:
   PlainOldClass() : x(-72) {}
   int getX() const { return x; }
   void setX( int x )  { this->x = x; } // No confusion!
private:
   int x;
};

class Colour {  
public:       
    Colour( const string& name, unsigned r, unsigned g, unsigned b )       
        : name(name), r(r), g(g), b(b) {}       
    void display() const { 
        cout << name << " (RBG: " << r << "," << g<< "," << b << ")"; 
    }   
private:       
    string   name;    // what we call this color       
    unsigned r, g, b; // red/green/blue values for displaying  
};     

int main() {
  Complex c = {11.23,45.67};      
  Complex* pC(&c);
  cout << "real: " << pC->real << "\nimaginary: " << pC->img << endl;
  PlainOldClass poc;
  PlainOldClass* ppoc( &poc );
  cout << ppoc->getX() << endl;
  ppoc->setX( 2837 );
  cout << ppoc->getX() << endl;

  int* pDyn = new int(3); // p points to an int initialized to 3 on the heap
  *pDyn = 17;
  cout << "The " << *pDyn << " is stored at address " << pDyn<< " which is in the heap\n";
  cout << pDyn << endl;  
  delete pDyn;  
  pDyn = NULL;
  cout << pDyn << endl;

  ifstream file("color.txt");
  if( !file ) {
    cerr << "Could not open the file." << endl;
    exit(1);
  }

  vector< Colour* > colours;         
  string inputName;       
  unsigned inputR, inputG, inputB;   // fill vector with Colours from the file       
  // this could be from a file but we are using the keyboard for now       
  // (do you remember the keystrokes to indicate "end of file" at the keyboard?)       
  while ( file >> inputName >> inputR >> inputG >> inputB ) {            
    colours.push_back( new Colour(inputName, inputR, inputG, inputB) );       
}         
  
  // display all the Colours in the vector:       
  for ( size_t ndx = 0; ndx < colours.size(); ++ndx ) {            
  colours[ndx]->display();            
  cout << endl;       
  }
}
