#ifndef NOBLE_H
#define NOBLE_H
#include <vector>
#include <string>

namespace WarriorCraft {

  class Warrior;
  
  class Noble {
    friend std::ostream& operator<<( std::ostream& os, const Noble& nob ); 
  public:
    ~Noble();
    Noble( const std::string& nobName ) : name(nobName) {}
    std::string getName() const;
    void hire( Warrior& name );
    void runaway( Warrior* addr );
    void battle( Noble& enemy );
  private:
    std::string name;
    std::vector<Warrior*> warriors;
  };

}

#endif
