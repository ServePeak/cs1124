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

void printFile( istream& file ) {
	/* Prints a file's text onto the screen, line by line. */
	string line;
	while( getline( file, line ) ) {
		cout << line << endl;
	}
	file.clear();
	file.seekg(0);
}

void addWarrior( vector<Warrior>& fighters, istringstream& sline ) {
  Warrior man;
  sline >> man.name;
  sline >> man.strength;
  cout << fighters.size() << endl; //debug
  fighters.push_back( man );
  cout << fighters.size() << endl; //debug
}

void compLine( const string line, vector<Warrior>& fighters ) {
  istringstream sline(line);
  string word;
  while( sline >> word ) {
    if( word == "Warrior" )  {
      addWarrior( fighters, sline );
      for( size_t i = 0; i < fighters.size(); i++ ) { //debug
	cout << fighters[i].name << endl;
      }
      cout << "Add warrior function here" << endl; //debug
    }
    else if( word == "Status" ) {
      cout << "Status function here" << endl; //debug
    }
    else if( word == "Battle" ) {
      cout << "Battle function here" << endl; //debug
    }
  }
}

int main() {
  string line;
  vector<Warrior> fighters;
  ifstream file( "warriors.txt" );
  if( !file ) {
    cerr << "Could not open the file." << endl;
    exit(1);
  }
  printFile( file );
  while( getline( file, line ) ) {
    compLine( line, fighters );
  }
  ofstream output( "output.txt" );
  file.close();
  output.close();
}
