/*
  hw00 / Caesar Cipher Decryption
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

void charDecrypt( const int num, char& ch ) {
  /* Changes a letter to a lower letter, by num amount. Returns the letter. */
  if( ch > 'a'+num-1 && ch <= 'z' ) {
    ch = ch - num;
  }
  // This is to loop around when ascii value goes under a.
  else if( ch <= 'a'+num-1 && ch >= 'a' ) {
    ch = ch - num + ALPHABET_SIZE;
  }
}

void lineDecrypt( const int num, string& decrypt ) {
  /* Changes a line's letters, passing to charDecrypt. */
  for( int i = 0; i < decrypt.size(); i++ ) {
    charDecrypt( num, decrypt[i] );
  }
}

vector<string> fileDecrypt( istream& file, const int num ) {
  /* Change's a files letters, passing to fileDecrypt,
     and prints by last line first. */
  vector<string> lines;
  string line;
  getline( file, line );
  while( getline( file, line ) ) {
    lineDecrypt( num, line );
    lines.push_back( line );
  }
  return lines;
}

void printVecRev( const vector<string>& vec ) {
  /* Prints all strings in a vector from last vector first. */
  for( int i = vec.size()-1; i >= 0; i-- ) {
    cout << vec[i] << endl;
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
  printVecRev( fileDecrypt( caesar, change ) );
  caesar.close();
}
