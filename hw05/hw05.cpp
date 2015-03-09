/*
	hw05 / Inheritance
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
  Warrior( const string& warName, double warStr ) : name(warName), strength(warStr), hired(false), dead(false) {}
  virtual string getName() const {
    return name;
  }
  virtual double getStr() const {
    return strength;
  }
  virtual void setStr( double strength ) {
    this->strength = strength;
  }
  virtual bool isHired() const {
    return hired;
  }
  virtual void flipHired() {
    hired = !hired;
  }
  virtual bool isDead() const {
    return dead;
  }
  virtual bool flipDead() {
    dead = !dead;
  } 
  virtual void defend( const string& name ) const = 0;
private:
  string name;
  double strength;
  bool hired;
  bool dead;
};

class Magician : public Warrior {
public:
  Magician( const string& name, double str ) : Warrior( name, str ) {}
  void defend( const string& name ) const {
    cout << "POOF!" << endl;
  };
private:
};

class Archer : public Warrior {
public:
  Archer( const string& name, double str ) : Warrior( name, str ) {}
  void defend( const string& name ) const {
    cout << "TWANG! " << Warrior::getName() << " says: Take that in the name of my lord, " << name << endl;
  }
private:
};

class Swordsman : public Warrior {
public:
  Swordsman( const string& name, double str ) : Warrior( name, str ) {}
  void defend( const string& name ) const {
    cout << "CLANG! " << Warrior::getName() << " says: Take that in the name of my lord, " << name << endl;
  }
private:
};

class Noble { 
public:
  Noble( const string& nobName ) : name(nobName), dead(false) {}
  Noble( const string& nobName, int str ) : name(nobName), strength(str), dead(false) {}
  virtual string getName() const {
    return name;
  }
  virtual bool isDead() const {
    return dead;
  }
  virtual double getStr() const = 0;
  virtual void setStr( double ratio ) = 0;
  virtual void battle( Noble& enemy );
private:
  string name;
  bool dead;
};

void Noble::battle( Noble& enemy ) {
  cout << getName() << " battles " << enemy.getName() << endl;
  double strength = getStr();
  double enStr = enemy.getStr();
  double ratio;

  // Gets a ratio depending on stronger Noble
  if( strength > enStr ) {
    ratio = enStr / strength;
  }
  else if( enStr > strength ) {
    ratio = strength / enStr;
  }

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

class PersonWithStrengthToFight : public Noble {
public:
  PersonWithStrengthToFight( const string& name, double str ) : Noble(name), strength(str) {}
  double getStr() const {
    return strength;
  }
  void setStr( double ratio ) {
    strength *= ratio;
  }
private:
  int strength;
};

class Lord : public Noble {
public:
  Lord( const string& name ) : Noble(name) {}
  void hires( Warrior& war ) {
    if( war.isHired() ) {
      cerr << war.getName() << " is already hired." << endl;
    }
    else if( Noble::getStr() == 0 ) {
      cerr << Noble::getName() << " is dead." << endl;
    }
    else if( war.getStr() == 0 ) {
      cerr << war.getName() << " is dead." << endl;
    } else {
      war.flipHired();
      warriors.push_back( &war );
    }
  }
  double getStr() const {
    double strength = 0;
    for( size_t i = 0; i < warriors.size(); i++ ) {
      strength += warriors[i]->getStr();
    }
    return strength;
  }
  void setStr( double ratio ) {
    for( size_t i = 0; i < warriors.size(); i++ ) {
      warriors[i]->setStr( warriors[i]->getStr() * ratio );
    }
  }
private:
  vector<Warrior*> warriors;
};

int main() {
  Archer george( "George", 150 );
  Lord sam( "Sam" );
  sam.hires( george );
}
