#ifndef WARRIOR_H
#define WARRIOR_H
#include <string>

namespace WarriorCraft {
  
  class Noble;

  class Warrior {
  public:
    ~Warrior();
    Warrior( const std::string& warName, double warStr ) : name(warName), strength(warStr) {}
    std::string getName() const;
    double getStr() const;
    void setStr( double str );
    void setNoble( Noble* addr );
    void runaway();
  private:
    std::string name;
    double strength;
    Noble* noble;
  };

}

#endif
