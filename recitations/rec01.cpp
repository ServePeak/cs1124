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

void printFile( ifstream& file ) {
	/* Prints a file's text onto the screen, line by line. */
	string line;
	while( getline( file, line ) ) {
		cout << line << endl;
	}
	file.clear();
	file.seekg(0);
}

int countWords( istream& file ) {
	/* Counts the number of words in a file and returns that. */
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
	printFile( file );
	cout << countWords( file ) << endl;
	file.close();
}
