/*
  hw04 / Dynamic Memory
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

class Warrior {
public: 
  Warrior( const string& warName, const int& warStr ) : name( warName ), strength( warStr ) {}
  string getName() const {
    return name;
  }
  int getStr() const {
    return strength;
  }
  void setStr( int strength ) {
    this->strength = strength;
  }
  void display( ostream& os = cout ) const {
    os << name << ": " << strength << endl;
  }
private:
  string name;
  double strength;
};

class Noble {
public:
  Noble( const string& nobName ) : name( nobName ) {}
  void hire( Warrior* warrior ) {
    warriors.push_back( warrior );
  }
  string getName() const {
    return name;
  }
  void display( ostream& os = cout ) const {
    os << name << " has an army of " << warriors.size() << endl;
    for( Warrior* war : warriors ) {
      os << '\t' << war->getName() << ": " << war->getStr() << endl;
    }
  }
  // Finds warrior, takes him out of nobles vector, then returns warrior
  Warrior* fire( string warrior, ostream& os = cout ) {
    Warrior* guy;
    for( size_t i = 0; i < warriors.size(); i++ ) {
      if( i != warriors.size()-1 && warriors[i]->getName() == warrior ) {
	Warrior* temp(warriors[i]);
	warriors[i] = warriors[i+1];
	warriors[i+1] = temp;
	temp = NULL;
      }
      else if( warriors[i]->getName() == warrior ) {
	guy = warriors[i];
	warriors.pop_back();
      }
    }
    os << "You don't work for me anymore " << warrior << "! -- " << getName() << '.' << endl;
    return guy;
  }
  void clear() {
    for( size_t i = 0; i < warriors.size(); i++ ) {
      delete warriors[i];
      warriors[i] = NULL;
    }
    warriors.clear();
  }
  void battle( Noble& enemy, ostream& os );
private:
  string name;
  vector<Warrior*> warriors;
};

void Noble::battle( Noble& enemy, ostream& os = cout ) {
  os << getName() << " battles " << enemy.getName() << endl;
  double strength = 0;
  double enStr = 0;
  double ratio;


  // Gets strength of both warriors, then gets ratio depending on who's stronger
  for( size_t i = 0; i < warriors.size(); i++ ) {
    strength += warriors[i]->getStr();
  }
  for( size_t i = 0; i < enemy.warriors.size(); i++ ) {
    enStr += enemy.warriors[i]-> getStr();
  }
  if( strength > enStr ) {
    ratio = enStr / strength;
  }
  else if( enStr > strength ) {
    ratio = strength / enStr;
  }
  //cout << strength << endl;
  //cout << enStr << endl;
  //cout << ratio << endl;

  // When both nobles have 0 strength
  if( strength == 0 && enStr == 0 ) {
    os << "Oh, NO! They're both dead! Yuck!" << endl;
  }
  // When both nobles have equal strength
  else if( strength == enStr ) {
    for( size_t i = 0; i < warriors.size(); i++ ) {
      warriors[i]->setStr(0);
    }
    for( size_t i = 0; i < enemy.warriors.size(); i++ ) {
      enemy.warriors[i]->setStr(0);
    }
    os << "Mutual Annihalation: " << getName() << " and " << enemy.getName() << " die at each other's hands" << endl; 
  }
  // When first noble has 0 strength
  else if( strength == 0 ) {
    os << "He's dead, " << enemy.getName() << endl;
  }
  // When second noble has 0 strength
  else if( enStr == 0 ) {
    os << "He's dead, " << getName() << endl;
  }
  // When first noble has more strength than the second fighter
  else if( strength > enStr ) {
    for( size_t i = 0; i < warriors.size(); i++ ) {
      warriors[i]->setStr( warriors[i]->getStr() * ratio );
    }
    for( size_t i = 0; i < enemy.warriors.size(); i++ ) {
      enemy.warriors[i]->setStr(0);
    }
    os << getName() << " defeats " << enemy.getName() << endl;
  }
  // When second noble has more strength than the first fighter
  else if( enStr > strength ) {
    for( size_t i = 0; i < enemy.warriors.size(); i++ ) {
      enemy.warriors[i]->setStr( enemy.warriors[i]->getStr() * ratio );
    }
    for( size_t i = 0; i < warriors.size(); i++ ) {
      warriors[i]->setStr(0);
    }
    os << enemy.getName() << " defeats " << getName() << endl;
  }
}

void addNoble( vector<Noble*>& nobles, ifstream& file, ostream& os = cout ) {
  string name;
  bool exists = false;
  file >> name;
  for( size_t i = 0; i < nobles.size(); i++ ) {
    if( nobles[i]->getName() == name ) {
      exists = true;
    }
  }
  if( exists ) {
    os << "Noble already exists" << endl;
  } else {
  Noble* someNoble = new Noble( name );
  nobles.push_back( someNoble );
  }
}

void addWarrior( vector<Warrior*>& warriors, ifstream& file, ostream& os = cout ) {
  string name;
  int strength;
  bool exists = false;
  file >> name >> strength;
  for( size_t i = 0; i < warriors.size(); i++ ) {
    if( warriors[i]->getName() == name ) {
      exists = true;
    }
  }
  if( exists ) {
    os << "Warrior already exists" << endl;
  } else {
  Warrior* someWarrior = new Warrior( name, strength );
  warriors.push_back( someWarrior );
  }
}

void hireWarrior( vector<Noble*>& nobles, vector<Warrior*>& warriors, ifstream& file, ostream& os = cout ) {
  string noble, warrior;
  bool exists = false;
  file >> noble >> warrior;
  for( size_t i = 0; i < warriors.size(); i++ ) {
    // If the warrior is found, pushes to end of vector to pop_back
    if( i != warriors.size()-1 && warriors[i]->getName() == warrior ) {
      Warrior* temp(warriors[i]);
      warriors[i] = warriors[i+1];
      warriors[i+1] = temp;
      temp = NULL;
    }
    // When warrior is at the end, he gets hired by noble and leaves the vector of unemployed warriors
    else if( warriors[i]->getName() == warrior ) {
      for( size_t j = 0; j < nobles.size(); j++ ) {
	if( nobles[j]->getName() == noble ) {
	  nobles[j]->hire( warriors[i] );
	  exists = true;
	}
      }
      warriors.pop_back();
    }
  }
  if( !exists ) {
    os << "Warrior has already been hired" << endl;
  }
}

void fireWarrior( vector<Noble*>& nobles, vector<Warrior*>& warriors, ifstream& file, ostream& os = cout ) {
  string noble, warrior;
  file >> noble >> warrior;
  for( size_t i = 0; i < nobles.size(); i++ ) {
    if( nobles[i]->getName() == noble ) {
      warriors.push_back( nobles[i]->fire( warrior, os ) );
    }
  }
}

void showStatus( vector<Noble*> nobles, vector<Warrior*> warriors, ostream& os = cout ) {
  os << "Status" << endl << "======" << endl << "Nobles" << endl;
  // Check if there are any nobles in the first place
  if( nobles.size() == 0 ) {
    os << "NONE" << endl;
  } else {
    for( size_t i = 0; i < nobles.size(); i++ ) {
      nobles[i]->display( os );
    }
  }
  os << "Unemployed Warriors:" << endl;
  // Check if there are any warriors in the first place
  if( warriors.size() == 0 ) {
    os << "NONE" << endl;
  } else {
    for( size_t i = 0; i < warriors.size(); i++ ) {
      warriors[i]->display( os );
    }
  }
}

void toBattle( vector<Noble*> nobles, ifstream& file, ostream& os = cout ) {
  string fNoble, sNoble;
  Noble* nblptr;
  file >> fNoble >> sNoble;
  // Gets second noble's pointer 
  for( size_t i = 0; i < nobles.size(); i++ ) {
    if( nobles[i]->getName() == sNoble ) {
      nblptr = nobles[i];
    }
  }
  // Uses second noble's pointer in first noble's battle function
  for( size_t i = 0; i < nobles.size(); i++ ) {
    if( nobles[i]->getName() == fNoble ) {
      nobles[i]->battle( *nblptr, os );
    }
  }
}

// Clears heapspace by deleting noble and warrior, then setting to null before clearing
void clearVecs( vector<Noble*>& nobles, vector<Warrior*>& warriors ) {
  for( size_t i = 0; i < nobles.size(); i++ ) {
    delete nobles[i];
    nobles[i] = NULL;
  }
  nobles.clear();
  for( size_t i = 0; i < warriors.size(); i++ ) {
    delete warriors[i];
    warriors[i] = NULL;
  }
  warriors.clear();
}

int main() {
  string word;
  vector<Noble*> nobles;
  vector<Warrior*> warriors;
  ifstream file( "war.txt" );
  ofstream output( "output.txt" );
  if( !file ) {
    cerr << "Could not open the file." << endl;
    exit(1);
  }
  // Reads file word by word checking for certain words
  while( file >> word ) {
    if( word == "Noble" )  {
      addNoble( nobles, file, output );
    }
    if( word == "Warrior" ) {
      addWarrior( warriors, file, output );
    }
    if( word == "Hire" ) {
      hireWarrior( nobles, warriors, file, output );
    }
    if( word == "Fire" ) {
      fireWarrior( nobles, warriors, file, output );
    }
    if( word == "Status" ) {
      showStatus( nobles, warriors, output );
    }
    if( word == "Battle" ) {
      toBattle( nobles, file, output );
    }
    if( word == "Clear" ) {
      clearVecs( nobles, warriors );
    }
  }
  file.close();
  output.close();
}
