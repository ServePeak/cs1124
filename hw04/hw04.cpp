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
  void display( ostream& os = cout ) {
    os << name << " has an army of " << warriors.size() << endl;
    for( Warrior* war : warriors ) {
      os << '\t' << war->getName() << ": " << war->getStr() << endl;
    }
  }
  Warrior* fire( string warrior ) {
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
    return guy;
  }
  void battle( Noble& enemy );
private:
  string name;
  vector<Warrior*> warriors;
};

void Noble::battle( Noble& enemy ) {
  cout << getName() << " battles " << enemy.getName() << endl;
  double strength = 0;
  double enStr = 0;
  double ratio;

  for( size_t i = 0; i < warriors.size(); i++ ) {
    strength += warriors[i]->getStr();
  }
  for( size_t i = 0; i < enemy.warriors.size(); i++ ) {
    enStr += enemy.warriors[i]-> getStr();
  }
  if( strength > enStr ) {
    ratio = strength / enStr;
  }
  else if( enStr > strength ) {
    ratio = enStr / strength;
  }
  //cout << strength << endl;
  //cout << enStr << endl;
  //cout << ratio << endl;

  // When both nobles have 0 strength
  if( strength == 0 && enStr == 0 ) {
    cout << "Oh, NO! They're both dead! Yuck!" << endl;
  }
  // When both nobles have equal strength
  else if( strength == enStr ) {
    for( size_t i = 0; i < warriors.size(); i++ ) {
      warriors[i]->setStr(0);
    }
    for( size_t i = 0; i < enemy.warriors.size(); i++ ) {
      enemy.warriors[i]->setStr(0);
    }
    cout << "Mutual Annihalation: " << getName() << " and " << enemy.getName() << " die at each other's hands" << endl; 
  }
  // When first noble has 0 strength
  else if( strength == 0 ) {
    cout << "He's dead, " << enemy.getName() << endl;
  }
  // When second noble has 0 strength
  else if( enStr == 0 ) {
    cout << "He's dead, " << getName() << endl;
  }
  // When first noble has more strength than the second fighter
  else if( strength > enStr ) {
    for( size_t i = 0; i < warriors.size(); i++ ) {
      warriors[i]->setStr( warriors[i]->getStr() * ratio );
    }
    for( size_t i = 0; i < enemy.warriors.size(); i++ ) {
      enemy.warriors[i]->setStr(0);
    }
    cout << getName() << " defeats " << enemy.getName() << endl;
  }
  // When second noble has more strength than the first fighter
  else if( enStr > strength ) {
    for( size_t i = 0; i < enemy.warriors.size(); i++ ) {
      enemy.warriors[i]->setStr( enemy.warriors[i]->getStr() * ratio );
    }
    for( size_t i = 0; i < warriors.size(); i++ ) {
      warriors[i]->setStr(0);
    }
    cout << enemy.getName() << " defeats " << getName() << endl;
  }
}

void addNoble( vector<Noble*>& nobles, ifstream& file ) {
  string name;
  file >> name;
  Noble* someNoble = new Noble( name );
  nobles.push_back( someNoble );
  //for( size_t i = 0; i < nobles.size(); i++ ) {
  //  cout << nobles[i]->getName() << endl;
  //}
}

void addWarrior( vector<Warrior*>& warriors, ifstream& file ) {
  string name;
  int strength;
  file >> name >> strength;
  Warrior* someWarrior = new Warrior( name, strength );
  warriors.push_back( someWarrior );
  //for( size_t i = 0; i < warriors.size(); i++ ) {
  //  cout << warriors[i]->getName() << ' ' << warriors[i]->getStr() << endl;
  //}
}

void hireWarrior( vector<Noble*>& nobles, vector<Warrior*>& warriors, ifstream& file ) {
  string noble, warrior;
  file >> noble >> warrior;
  for( size_t i = 0; i < warriors.size(); i++ ) {
    if( i != warriors.size()-1 && warriors[i]->getName() == warrior ) {
      Warrior* temp(warriors[i]);
      warriors[i] = warriors[i+1];
      warriors[i+1] = temp;
      temp = NULL;
    }
    else if( warriors[i]->getName() == warrior ) {
      for( size_t j = 0; j < nobles.size(); j++ ) {
	if( nobles[j]->getName() == noble ) {
	  nobles[j]->hire( warriors[i] );
	}
      }
      warriors.pop_back();
    }
  }
}

void fireWarrior( vector<Noble*>& nobles, vector<Warrior*>& warriors, ifstream& file ) {
  string noble, warrior;
  file >> noble >> warrior;
  for( size_t i = 0; i < nobles.size(); i++ ) {
    if( nobles[i]->getName() == noble ) {
      warriors.push_back( nobles[i]->fire( warrior ) );
    }
  }
}

void showStatus( vector<Noble*> nobles, vector<Warrior*> warriors ) {
  cout << "Status" << endl << "======" << endl << "Nobles" << endl;
  for( size_t i = 0; i < nobles.size(); i++ ) {
    nobles[i]->display();
  }
  cout << "Unemployed Warriors:" << endl;
  for( size_t i = 0; i < warriors.size(); i++ ) {
    warriors[i]->display();
  }
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
      addNoble( nobles, file );
    }
    if( word == "Warrior" ) {
      addWarrior( warriors, file );
    }
    if( word == "Hire" ) {
      hireWarrior( nobles, warriors, file );
    }
    if( word == "Fire" ) {
      fireWarrior( nobles, warriors, file );
    }
    if( word == "Status" ) {
      showStatus( nobles, warriors );
    }
  }
  file.close();
  output.close();
}
