/*
	rec03 - sandwich shop
	Jia Sen Wu / jw3675
	CS1124
	Polytechnic University
*/

#include <iostream>
#include <vector>
#include <stdlib.h>
using namespace std;

class Sandwich {
public: 
  Sandwich( int nCheese=1, double nMayo=1, int nTomato=2, double nMustard=.05 ) : \
    cheese(nCheese), mayo(nMayo), tomato(nTomato), mustard(nMustard) {}
  void display( ostream& os = cout ) const {
    // displays in single line
    os << "Bread: " << bread << ", " << "Cheese: " << cheese << ", " << "Mayo: " << \
      mayo << ", " << "Tomato: " << tomato << ", " << "Mustard: " << mustard << endl;
  }
  int getCheese() const {
    return tomato;
  }
  void setCheese( int nCheese ) {
    cheese = nCheese;
  }
  double getMayo() const {
    return mayo;
  }
  void setMayo( double nMayo ) {
    mayo = nMayo;
  }
  int getTomato() const {
    return tomato;
  }
  void setTomato( int nTomato ) {
    tomato = nTomato;
  }
  double getMustard() const {
    return mustard;
  }
  void setMustard( double nMustard ) {
    mustard = nMustard;
  }

private:
  static const int bread = 2; // ubuntu g++ -std=c++0x forced this or else implicitly deleted
  int cheese;
  double mayo;
  int tomato;
  double mustard;
};

class SandwichTruck {
public:
  void addSandwich( const Sandwich& sandwich ) {
    sandwiches.push_back( sandwich );
  }
  void display() const {
    // using for loop instead of for each so it returns non-copy
    for( size_t i=0; i < sandwiches.size(); i++ ) {
      sandwiches[i].display();
    }
  }

private:
  vector<Sandwich> sandwiches;
};

int main() {
  Sandwich one;
  Sandwich two;
  two.setMustard(0); // changed their mind to no mustard
  Sandwich three( 2 ); // extra cheese
  Sandwich four;
  SandwichTruck truck;
  truck.addSandwich(one);
  truck.addSandwich(two);
  truck.addSandwich(three);
  truck.addSandwich(four);
  truck.display();
  cout << two.getMustard() << endl;
}
