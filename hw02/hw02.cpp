/*
  hw02 / Warrior Battle Simulator
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
  Weapon( const string& theName, const int& theStr ) : name( theName ), strength( theStr ) {} 
  string name;
  int strength;
};

class Warrior {
public: 
  Warrior( const string& warName, const string& wepName, const int& wepStr ) : name( warName ), wepn( wepName, wepStr ) {}
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
  void battle( Warrior& enemy, ostream& out );
private:
  string name;
  Weapon wepn;
};

void Warrior::battle( Warrior& enemy, ostream& out ) {
  out << getName() << " battles " << enemy.getName() << endl;
  cout << getName() << " battles " << enemy.getName() << endl;
  
  // When both fighters have 0 strength
  if( getWepStr() == 0 && enemy.getWepStr() == 0 ) {
    out << "Oh, NO! They're both dead! Yuck!" << endl;
    cout << "Oh, NO! They're both dead! Yuck!" << endl;
  }
  // When both fighters have equal strength
  else if( getWepStr() == enemy.getWepStr() ) {
    setWepStr(0);
    enemy.setWepStr(0);
    out << "Mutual Annihilations: " << getName() << " and " << enemy.getName() << " die at each other's hands" << endl;
    cout << "Mutual Annihilations: " << getName() << " and " << enemy.getName() << " die at each other's hands" << endl;
  }
  // When first fighter has 0 strength
  else if( getWepStr() == 0 ) {
    out << "He's dead, " << enemy.getName() << endl;
    cout << "He's dead, " << enemy.getName() << endl;
  }
  // When second fighter has 0 strength
  else if( enemy.getWepStr() == 0 ) {
    out << "He's dead, " << getName() << endl;
    cout << "He's dead, " << getName() << endl;
  }
  // When first fighter has more strength than the second fighter
  else if( getWepStr() > enemy.getWepStr() ) {
    setWepStr( getWepStr() - enemy.getWepStr() );
    enemy.setWepStr(0);
    out << getName() << " defeats " << enemy.getName() << endl;
    cout << getName() << " defeats " << enemy.getName() << endl;
  }
  // When second fighter has more strength than the first fighter
  else if( enemy.getWepStr() > getWepStr() ) {
    enemy.setWepStr( enemy.getWepStr() - getWepStr() );
    setWepStr(0);
    out << enemy.getName() << " defeats " << getName() << endl;
    cout << enemy.getName() << " defeats " << getName() << endl;
  }
}

void addWarrior( vector<Warrior>& fighters, istringstream& sline ) {
  /* Adds a warrior to a given vector from a stringstream */
  string name;
  string wname;
  int wstr;
  sline >> name >> wname >> wstr;
  Warrior man( name, wname, wstr );
  fighters.push_back( man );
}

void printStatus( const vector<Warrior> fighters, ostream& out ) {
  /* Prints the number of warriors, and status of each warrior */
  out << "There are: " << fighters.size() << " warriors" << endl;
  for( const Warrior war : fighters ) { 
    // Ex: Warrior: Lorem, weapon: Ipsum, 32
    out << "Warrior: " << war.getName() << ", " << "weapon: " << war.getWepName() << ", " << war.getWepStr() << endl;
    cout << "Warrior: " << war.getName() << ", " << "weapon: " << war.getWepName() << ", " << war.getWepStr() << endl;
  }
}

void toBattle( vector<Warrior>& fighters, istringstream& sline, ostream& out ) {
  /* Prints what happens when two warriors fight, and modifies accordingly */
  int fFi;
  int sFi;
  string word;
  sline >> word;
  // Finds fighter in vector and gets index
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
  fighters[fFi].battle( fighters[sFi], out );
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
