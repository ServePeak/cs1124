/*
	Caesar Cipher Decryption
	Jia Sen Wu
	CS1124
	Polytechnic University
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int ALPHABET_SIZE = 26;

int charDecrypt( int num, char ch ) {
	if( ch > 101 && ch <= 122 ) {
		return static_cast<char>( ch - num );
	}
	else if( ch <= 101 && ch >= 92 ) {
		return static_cast<char>( ch - num + ALPHABET_SIZE );
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

void fileToVec( istream& file ) {
	string aString;
	vector<string> lines;
	
	while( file >> aString ) {
		lines.push_back( aString );
	return lines;
}

int main() {
	int change = 5;
	string decrypted;
	vector<string> lines;
	
	ifstream caesar( "encrypted.txt" );
	if( !caesar ) {
		cerr << "Could not open the file." << endl;
		exit(1);
	}
	lines = fileToVec( caesar );
	for( int i = lines.size()-1; i >= 0; i-- ) {
		decrypted += lineDecrypt( change, "test" ) + endl;
	}
	cout << decrypted;
	caesar.close();
}
