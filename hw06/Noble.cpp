#include "Noble.h"
#include "Warrior.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;

namespace WarriorCraft {

  Noble::~Noble() {
  }

  string Noble::getName() const {
    return name;
  }

  void Noble::hire( Warrior& name ) {
    warriors.push_back( &name );
    name.setNoble( this );
  }

  void Noble::runaway( Warrior* addr ) {
    // If finds Warrior, moves it to back to pop.
    // This method will only get called by warrior's runaway, so the warrior will always exist
    for( size_t i = 0; i < warriors.size(); i++ ) {
      if( addr == warriors[i] ) {
      Warrior* tmp = warriors[i];
      warriors[i] = warriors[i+1];
      warriors[i+1] = tmp;
      }
    }
    warriors.pop_back();
  }

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

  ostream& operator<<( ostream& os, const Noble& nob ) {
    os << nob.name << " has an army of " << nob.warriors.size() << endl;
    // Loops to find warrior name and strength
    for( size_t i = 0; i < nob.warriors.size(); i++ ) {
      os << '\t' << nob.warriors[i]->getName() << ": " << nob.warriors[i]->getStr() << endl;
    }
    return os; // Don't forget this
  }

}
