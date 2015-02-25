/*
	hw01 / Warrior Battle Simulator
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
  void setStr( const int& strength ) {
    this->strength = strength;
  }
  void battle( Warrior& enemy, ostream& out );
private:
  string name;
  int strength;
};

class Noble {
public:
  Noble( const string& nobName ) : name( nobName ) {}
  void hire( Warrior& warrior ) {
    warriors.push_back( &warrior );
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
	warriors[i] = NULL;
	warriors.erase(i);
      }
    }
  }
private:
  string name;
  vector<Warrior*> warriors;
};

void Warrior::battle( Warrior& enemy, ostream& out ) {
  out << getName() << " battles " << enemy.getName() << endl;
  cout << getName() << " battles " << enemy.getName() << endl;
  
  // When both fighters have 0 strength
  if( getStr() == 0 && enemy.getStr() == 0 ) {
    out << "Oh, NO! They're both dead! Yuck!" << endl;
    cout << "Oh, NO! They're both dead! Yuck!" << endl;
  }
  // When both fighters have equal strength
  else if( getStr() == enemy.getStr() ) {
    setStr(0);
    enemy.setStr(0);
    out << "Mutual Annihilations: " << getName() << " and " << enemy.getName() << " die at each other's hands" << endl;
    cout << "Mutual Annihilations: " << getName() << " and " << enemy.getName() << " die at each other's hands" << endl;
  }
  // When first fighter has 0 strength
  else if( getStr() == 0 ) {
    out << "He's dead, " << enemy.getName() << endl;
    cout << "He's dead, " << enemy.getName() << endl;
  }
  // When second fighter has 0 strength
  else if( enemy.getStr() == 0 ) {
    out << "He's dead, " << getName() << endl;
    cout << "He's dead, " << getName() << endl;
  }
  // When first fighter has more strength than the second fighter
  else if( getStr() > enemy.getStr() ) {
    setStr( getStr() - enemy.getStr() );
    enemy.setStr(0);
    out << getName() << " defeats " << enemy.getName() << endl;
    cout << getName() << " defeats " << enemy.getName() << endl;
  }
  // When second fighter has more strength than the first fighter
  else if( enemy.getStr() > getStr() ) {
    enemy.setStr( enemy.getStr() - getStr() );
    setStr(0);
    out << enemy.getName() << " defeats " << getName() << endl;
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
  //art.hire(wizard);
  lance.hire(dylan);
  linus.hire(lawless);
  billie.hire(mrGreen);
  art.hire(cheetah);
  art.hire(wizard);
  
  jim.display();
  lance.display();
  art.display();
  linus.display();
  billie.display();
  
  art.fire(cheetah);
  art.display();
  /*
  art.battle(lance);
  jim.battle(lance);
  linus.battle(billie);
  billie.battle(lance);*/
}
