/*
	Caesar Cipher Decryption
	Jia Sen Wu
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
	string finals;
	for( int i = 0; i < decrypt.size(); i++ ) {
		finals += charDecrypt( num, decrypt[i] );
	}
	return finals;
}

void fileDecrypt( istream& file, int num ) {
    string line;
    getline( file, line );
    while( getline( file, line ) ) {
      cout << lineDecrypt( num, line ) << endl;
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
