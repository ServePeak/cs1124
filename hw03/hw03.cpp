/*
  hw03 / Warrior Battle Simulator
  Jia Sen Wu / jw3675
  CS1124
  Polytechnic University
*/

#include <fstream>
#include <iostream>
#include <sstream>
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
private:
  string name;
  double strength;
};

class Noble {
public:
  Noble( const string& nobName ) : name( nobName ) {}
  void hire( Warrior& warrior ) {
    warriors.push_back( &warrior );
  }
  string getName() const {
    return name;
  }
  void display() {
    cout << name << " has an army of " << warriors.size() << endl;
    for( Warrior* war : warriors ) {
      cout << '\t' << war->getName() << ": " << war->getStr() << endl;
    }
  }
  void fire( Warrior& warrior ) {
    for( size_t i = 0; i < warriors.size(); i++ ) {
      if( warriors[i]->getName() == warrior.getName() ) {
	warriors.erase(warriors.begin()+i);
      }
    }
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

int main() {
  Noble art("King Arthur");
  Noble lance("Lancelot du Lac");
  Noble jim("Jim");
  Noble linus("Linus Torvalds");
  Noble billie("Bill Gates");
  
  Warrior cheetah("Tarzan", 10);
  Warrior wizard("Merlin", 15);
  Warrior theGovernator("Conan", 12);
  Warrior nimoy("Spock", 15);
  Warrior lawless("Xena", 20);
  Warrior mrGreen("Hulk", 8);
  Warrior dylan("Hercules", 3);
  
  jim.hire(nimoy);
  lance.hire(theGovernator);
  art.hire(wizard);
  lance.hire(dylan);
  linus.hire(lawless);
  billie.hire(mrGreen);
  art.hire(cheetah);
  
  jim.display();
  lance.display();
  art.display();
  linus.display();
  billie.display();
  
  art.fire(cheetah);
  art.display();
  
  art.battle(lance);
  jim.battle(lance);
  linus.battle(billie);
  billie.battle(lance);
}
