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

class Wizard : public Warrior {
public:
  Wizard( const string& name, double str ) : Warrior( name, str ) {}
  // It is such a hard job to control the strength expended with magic!
  void defend( const string& name ) const {
    cout << "POOF!" << endl;
  };
private:
};

class Archer : public Warrior {
public:
  Archer( const string& name, double str ) : Warrior( name, str ) {}
  void defend( const string& name ) const {
    cout << "TWANG! " << getName() << " says: Take that in the name of my lord, " << name << endl;
  }
private:
};

class Swordsman : public Warrior {
public:
  Swordsman( const string& name, double str ) : Warrior( name, str ) {}
  void defend( const string& name ) const {
    cout << "CLANG! " << getName() << " says: Take that in the name of my lord, " << name << endl;
  }
private:
};

class Noble { 
public:
  Noble( const string& nobName ) : name(nobName), dead(false) {}
  virtual string getName() const {
    return name;
  }
  virtual bool isDead() const {
    return dead;
  }
  virtual void flipDead() {
    dead = !dead;
  }
  virtual double getStr() const = 0;
  virtual void setStr( double ratio ) = 0;
  virtual void doBattle(){}; // This is so that the warriors can say something
  virtual void battle( Noble& enemy );
private:
  string name;
  bool dead;
};

void Noble::battle( Noble& enemy ) {
  cout << getName() << " battles " << enemy.getName() << endl;
  Noble* const thyself = &enemy;
  // Polymorphism
  double strength = this->getStr();
  double enStr = thyself->getStr();
  double ratio;
  // cout << strength << ',' << enStr << endl;

  // Gets a ratio depending on stronger Noble
  if( strength > enStr ) {
    ratio = enStr / strength;
  }
  else if( enStr > strength ) {
    ratio = strength / enStr;
  }

  // When both nobles are dead
  if( this->isDead() && thyself->isDead() ) {
    cout << "Oh, NO! They're both dead! Yuck!" << endl;
  }
  // When both nobles have equal strength
  else if( strength == enStr ) {
    this->setStr(0);
    thyself->setStr(0);
    this->doBattle();
    thyself->doBattle();
    cout << "Mutual Annihilation: " << this->getName() << " and " << thyself->getName() << " die at each other's hands" << endl; 
  }
  // When first noble is dead
  else if( this->isDead() ) {
    cout << "He's dead, " << thyself->getName() << endl;
  }
  // When second noble is dead
  else if( thyself->isDead() ) {
    cout << "He's dead, " << this->getName() << endl;
  }
  // When first noble has more strength than the second fighter
  else if( strength > enStr ) {
    this->setStr( this->getStr() * ratio );
    thyself->setStr(0);
    this->doBattle();
    thyself->doBattle();
    cout << this->getName() << " defeats " << thyself->getName() << endl;
  }
  // When second noble has more strength than the first fighter
  else if( enStr > strength ) {
    this->setStr(0);
    thyself->setStr( thyself->getStr() * ratio );
    this->doBattle();
    thyself->doBattle();
    cout << thyself->getName() << " defeats " << this->getName() << endl;
  }
}

class PersonWithStrengthToFight : public Noble {
public:
  PersonWithStrengthToFight( const string& name, double str ) : Noble(name), strength(str) {}
  double getStr() const {
    return strength;
  }
  void setStr( double ratio ) {
    if( ratio == 0 ) {
      flipDead();
      strength = 0;
    } else {
      strength *= ratio;
    }
  }
private:
  int strength;
};

class Lord : public Noble {
public:
  Lord( const string& name ) : Noble(name) {}
  void hires( Warrior& war ) {
    if( war.isHired() ) {
      //cerr << war.getName() << " is already hired." << endl;
    }
    else if( isDead() ) {
      //cerr << getName() << " is dead and cannot hire " << war.getName() << '.' << endl;
    }
    else if( war.getStr() == 0 ) {
      //cerr << war.getName() << " is dead." << endl;
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
  // Man, this guy has a lot of work cut out for him
  // Whatever he does, his fellow warriors must have to same happen
  void setStr( double ratio ) {
    if( ratio == 0 ) {
      flipDead();
      for( size_t i = 0; i < warriors.size(); i++ ) {
	warriors[i]->setStr(0);
	warriors[i]->flipDead();
      }
    } else {
      for( size_t i = 0; i < warriors.size(); i++ ) {
	warriors[i]->setStr( warriors[i]->getStr() * ratio );
      }
    }
  }
  // Warriors, scream your battlecry!
  void doBattle() {
    for( size_t i = 0; i < warriors.size(); i++ ) {
      warriors[i]->defend( getName() );
    }
  }
private:
  vector<Warrior*> warriors;
};

int main() {
  Lord sam("Sam");
  Archer samantha("Samantha", 200);
  sam.hires(samantha);
  Lord joe("Joe");
  PersonWithStrengthToFight randy("Randolf the Elder", 250); 	
  joe.battle(randy);
  joe.battle(sam);	
  Lord janet("Janet");	
  Swordsman hardy("TuckTuckTheHardy", 100);
  Swordsman stout("TuckTuckTheStout", 80);
  janet.hires(hardy);	
  janet.hires(stout);	
  PersonWithStrengthToFight barclay("Barclay the Bold", 300);	
  janet.battle(barclay);	
  janet.hires(samantha);	
  Archer pethora("Pethora", 50);	
  Archer thora("Thorapleth", 60);
  Wizard merlin("Merlin", 150);
  janet.hires(pethora);
  janet.hires(thora);
  sam.hires(merlin);
  janet.battle(barclay);	
  sam.battle(barclay);	
  joe.battle(barclay);
}
