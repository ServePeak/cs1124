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

struct Warrior {
  string name;
  int strength;
};

void addWarrior( vector<Warrior>& fighters, istringstream& sline ) {
  /* Adds a warrior to a given vector */
  Warrior man;
  sline >> man.name;
  sline >> man.strength;
  fighters.push_back( man );
}

void printStatus( const vector<Warrior> fighters, ostream& out ) {
  /* Prints the number of warriors, and status of each */
  out << "There are: " << fighters.size() << " warriors" << endl;
  for( const Warrior war : fighters ) { 
    out << "Warrior: " << war.name << ", " << "strength: " << war.strength << endl;
  }
}

void toBattle( vector<Warrior>& fighters, istringstream& sline, ostream& out ) {
  /* Prints what happens when two warriors fight, and modifies accordingly */
  int fFi;
  int sFi;
  string word;
  sline >> word;
  for( size_t i = 0; i < fighters.size(); i++ ) { 
    if( fighters[i].name == word ) {
      fFi = i;
    }
  }
  sline >> word;
  for( size_t i = 0; i < fighters.size(); i++ ) { 
    if( fighters[i].name == word ) {
      sFi = i;
    }
  }
  out << fighters[fFi].name << " battles " << fighters[sFi].name << endl;

  // When both fighters have 0 strength
  if( fighters[fFi].strength == 0 && fighters[sFi].strength == 0 ) {
    out << "Oh, NO! They're both dead! Yuck!" << endl;
  }
  // When both fighters have equal strength
  else if( fighters[fFi].strength == fighters[sFi].strength ) {
    fighters[fFi].strength = fighters[sFi].strength = 0;
    out << "Mutual Annihilations: " << fighters[fFi].name << " and " << fighters[sFi].name << " die at each other's hands" << endl;
  }
  // When first fighters has 0 strength
  else if( fighters[fFi].strength == 0 ) {
    out << "He's dead, " << fighters[sFi].name << endl;
  }
  // When second fighter has 0 strength
  else if( fighters[sFi].strength == 0 ) {
    out << "He's dead, " << fighters[fFi].name << endl;
  }
  // When first fighter has more strength than the second fighter
  else if( fighters[fFi].strength > fighters[sFi].strength ) {
    fighters[fFi].strength -= fighters[sFi].strength;
    fighters[sFi].strength = 0;
    out << fighters[fFi].name << " defeats " << fighters[sFi].name << endl;
  }
  // When second fighter has more strength than the first fighter
  else if( fighters[sFi].strength > fighters[fFi].strength ) {
    fighters[sFi].strength -= fighters[fFi].strength;
    fighters[fFi].strength = 0;
    out << fighters[sFi].name << " defeats " << fighters[fFi].name << endl;
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
