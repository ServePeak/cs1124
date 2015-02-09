/*
	hw01 / Warrior Battle Simulator
	Jia Sen Wu / jw3675
	CS1124
	Polytechnic University
*/

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stdlib.h>
using namespace std;

class Weapon {
public:
  Weapon( const string& theName, const int& theStr ) : name( theName ), strength( theStr) {
 } 

  string name;
  int strength;
};

class Warrior {
public: 
  Warrior( const string& warName, const string& wepName, const int& wepStr ) : name( warName ), wepn( wepName, wepStr ) {
  }
  string getName() const {
    return name;
  }
  string getWepName() const {
    return wepn.name;
  }
  int getWepStr() const {
    return wepn.strength;
  }
  void setWepStr( const int& strength ) {
    wepn.strength = strength;
  }

private:
  string name;
  Weapon wepn;
};

void addWarrior( vector<Warrior>& fighters, istringstream& sline ) {
  /* Adds a warrior to a given vector */
  string name;
  string wname;
  int wstr;
  sline >> name >> wname >> wstr;
  Warrior man( name, wname, wstr );
  fighters.push_back( man );
}

void printStatus( const vector<Warrior> fighters, ostream& out ) {
  /* Prints the number of warriors, and status of each */
  out << "There are: " << fighters.size() << " warriors" << endl;
  for( const Warrior war : fighters ) { 
    out << "Warrior: " << war.getName() << ", " << "weapon: " << war.getWepName() << ", " << war.getWepStr() << endl;
  }
}

void toBattle( vector<Warrior>& fighters, istringstream& sline, ostream& out ) {
  /* Prints what happens when two warriors fight, and modifies accordingly */
  int fFi;
  int sFi;
  string word;
  sline >> word;
  for( size_t i = 0; i < fighters.size(); i++ ) { 
    if( fighters[i].getName() == word ) {
      fFi = i;
    }
  }
  sline >> word;
  for( size_t i = 0; i < fighters.size(); i++ ) { 
    if( fighters[i].getName() == word ) {
      sFi = i;
    }
  }
  out << fighters[fFi].getName() << " battles " << fighters[sFi].getName() << endl;

  // When both fighters have 0 strength
  if( fighters[fFi].getWepStr() == 0 && fighters[sFi].getWepStr() == 0 ) {
    out << "Oh, NO! They're both dead! Yuck!" << endl;
  }
  // When both fighters have equal strength
  else if( fighters[fFi].getWepStr() == fighters[sFi].getWepStr() ) {
    fighters[fFi].setWepStr(0);
    fighters[sFi].setWepStr(0);
    out << "Mutual Annihilations: " << fighters[fFi].getName() << " and " << fighters[sFi].getName() << " die at each other's hands" << endl;
  }
  // When first fighters has 0 strength
  else if( fighters[fFi].getWepStr() == 0 ) {
    out << "He's dead, " << fighters[sFi].getName() << endl;
  }
  // When second fighter has 0 strength
  else if( fighters[sFi].getWepStr() == 0 ) {
    out << "He's dead, " << fighters[fFi].getName() << endl;
  }
  // When first fighter has more strength than the second fighter
  else if( fighters[fFi].getWepStr() > fighters[sFi].getWepStr() ) {
    fighters[fFi].setWepStr( fighters[sFi].getWepStr() );
    fighters[sFi].setWepStr(0);
    out << fighters[fFi].getName() << " defeats " << fighters[sFi].getName() << endl;
  }
  // When second fighter has more strength than the first fighter
  else if( fighters[sFi].getWepStr() > fighters[fFi].getWepStr() ) {
    fighters[sFi].setWepStr( fighters[fFi].getWepStr() );
    fighters[fFi].setWepStr(0);
    out << fighters[sFi].getName() << " defeats " << fighters[fFi].getName() << endl;
  }
}

void compLine( const string line, vector<Warrior>& fighters, ostream& out ) {
  /* Reads a line, interpreting the first word to see if it's warrior, status, or battle */
  istringstream sline(line);
  string word;
  while( sline >> word ) {
    if( word == "Warrior" )  {
      addWarrior( fighters, sline );
    }
    else if( word == "Status" ) {
      printStatus( fighters, out );
    }
    else if( word == "Battle" ) {
      toBattle( fighters, sline, out );
    }
  }
}

int main() {
  string line;
  vector<Warrior> fighters;
  ifstream file( "warriors.txt" );
  ofstream output( "output.txt" );
  if( !file ) {
    cerr << "Could not open the file." << endl;
    exit(1);
  }
  // Reads file line by line to compLine
  while( getline( file, line ) ) {
    compLine( line, fighters, output );
  }
  file.close();
  output.close();
}
