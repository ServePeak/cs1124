/*
	rec01 - file reading
	Jia Sen Wu / jw3675
	CS1124
	Polytechnic University
*/

#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;

int countWords( istream& file ) {
  string aString;
  int count = 0;
  while( file >> aString ) {
    count++;
  }
  return count;
}

int main() {
  ifstream file( "test.txt" );
  if( !file ) {
    cerr << "Could not open the file." << endl;
    exit(1);
  }
  cout << countWords( file ) << endl;
  file.close();
}
