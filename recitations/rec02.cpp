/*
	rec02 - hydrocarbon sorter
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

struct Chemical {
  vector<string> name;
  int carbon;
  int hydrogen;
};

void addChem( const string& name, const int& carbon, const int& hydrogen, vector<Chemical>& chemicals ) {
  /* Creates a Chemical with carbon, hydrogen, and name, and pushes back to vector chemicals */
  Chemical chem;
  chem.name.push_back( name );
  chem.carbon = carbon;
  chem.hydrogen = hydrogen;
  chemicals.push_back( chem );
}

void addName( const string& name, const int& index, vector<Chemical>& chemicals ) {
  /* Adds name to a specific index of vector chemicals */
  chemicals[index].name.push_back( name );
}

int hasChem( const int& carbon, const int& hydrogen, vector<Chemical>& chemicals ) {
  /* Checks to see if the chemical already exists. If it does, return index, else return -1 */
  for( size_t i = 0; i < chemicals.size(); i++ ) {
    if( chemicals[i].carbon == carbon && chemicals[i].hydrogen == hydrogen ) {
      return i;
    }
  }
  return -1;
}

void parseLine( ifstream& file, vector<Chemical>& chemicals ) {
  /* Parses file */
  string line;
  string name;
  int index;
  int carbon;
  int hydrogen;
  char aChar;
  // Reads all the needed char/string/int in a line
  while( file >> name >> aChar >> carbon >> aChar >> hydrogen ) {
    index = hasChem( carbon, hydrogen, chemicals );
    // If cannot find index
    if( index == -1 ) {
      addChem( name, carbon, hydrogen, chemicals );
    } else {
      addName( name, index, chemicals );
    }
  }
}

void dispChem( const vector<Chemical>& chemicals ) {
  /* Displays chemicals in ascending carbon order */
  int max = 0;
  // Gets max carbon number
  for( Chemical chem : chemicals ) {
    if( chem.carbon > max ) {
      max = chem.carbon;
    }
  }
  // Loops from 0 to max carbon number, each time printing only chemicals that
  // have the specific carbon number
  for( int i = 1; i <= max; i++ ) {
    for( Chemical chem: chemicals ) {
      if( chem.carbon == i ) {
	cout << 'C' << chem.carbon << 'H' << chem.hydrogen << ' ';
	for( string names : chem.name ) {
	  cout << names << ' ';
	}
	cout << endl;
      }
    }
  }
}

int main() {
  vector<Chemical> chemicals;
  ifstream file( "hydrocarbons.txt" );
  if( !file ) {
    cerr << "Could not open the file." << endl;
    exit(1);
  }
  parseLine( file, chemicals );
  dispChem( chemicals );
  file.close();
}
