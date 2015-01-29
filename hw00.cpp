/*
	Caesar Cipher Decryption
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

const int ALPHABET_SIZE = 26;

char charDecrypt( int num, char ch ) {
	/* Changes a letter to a lower letter, by num amount. Returns the letter. */
	if( ch > 101 && ch <= 122 ) {
		return ch - num;
	}
	else if( ch <= 101 && ch >= 92 ) {
		return ch - num + ALPHABET_SIZE;
	}
	else {
		return ch;
	}
}

string lineDecrypt( int num, string decrypt ) {
	/* Changes a line's letters, passing to charDecrypt. Returns the line. */
	string finals;
	for( int i = 0; i < decrypt.size(); i++ ) {
		finals += charDecrypt( num, decrypt[i] );
	}
	return finals;
}

void fileDecrypt( istream& file, int num ) {
	/* Change's a files letters, passing to fileDecrypt,
and prints by last line first. */
  vector<string> lines;
	string line;
	getline( file, line );
	while( getline( file, line ) ) {
		lines.push_back( lineDecrypt( num, line ) );
	}
	for( int i = lines.size()-1; i >= 0; i-- ) {
		cout << lines[i] << endl;
	}
}

int main() {
	int change;
	ifstream caesar( "encrypted.txt" );
	if( !caesar ) {
		cerr << "Could not open the file." << endl;
		exit(1);
	}
	caesar >> change;
	fileDecrypt( caesar, change );
	caesar.close();
}
