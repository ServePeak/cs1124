#include <fstream>
#include <iostream>
using namespace std;

int main() {
  char line;
  int something;
  ifstream file( "test.txt" );
  file >> line;
  file >> something;
  cout << something << endl;
}
