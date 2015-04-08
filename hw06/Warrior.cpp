#include "Warrior.h"
#include "Noble.h"
#include <string>
#include <iostream>
using namespace std;

namespace WarriorCraft {

  Warrior::~Warrior() {
  }

  string Warrior::getName() const {
    return name;
  }

  double Warrior::getStr() const {
    return strength;
  }

  void Warrior::setStr( double str ) {
    strength = str;
  }

  void Warrior::setNoble( Noble* addr ) {
    noble = addr;
  }

  void Warrior::runaway() {
    cout << name << " flees in terror, abandoning his lord, " << noble->getName() << endl;
    noble->runaway(this);
    noble = NULL;
  }

}
