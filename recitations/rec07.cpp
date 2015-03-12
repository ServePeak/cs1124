/*
  hw07 / Association and Delegation
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

class Instrument {
public:
  virtual void makeSound() const = 0;
  virtual void play() const = 0;
private:
};

class Brass : public Instrument {
public:
  Brass( unsigned aSize ) : size(aSize) {}
  virtual void makeSound() const {
    cout << "To make a sound... blow on a mouthpiece of size " << size << endl;
  }
  virtual void play() const = 0;
private:
  unsigned size;
};

class String: public Instrument {
public:
  String( unsigned aPitch ) : pitch(aPitch) {}
  virtual void makeSound() const {
    cout << "To make a sound... bow a string with pitch " << pitch << endl;
  }
  virtual void play() const = 0;
private:
  unsigned pitch;
};

class Percussion : public Instrument {
public:
  virtual void makeSound() const {
    cout << "To make a sound... hit me!" << endl;
  }
  virtual void play() const = 0;
private:
};
/*
class Big : public Brass {
public:
  Big() : Brass(12) {}
private:
};

class Medium : public Brass {
public:
  Medium() : Brass(9) {}
private:
};

class Small : public Brass {
public:
  Small() : Brass(4) {}
private:
};
*/
class Trumpet : public Brass {
public:
  Trumpet( unsigned size ) : Brass(size) {}
  void play() const {
    cout << "Toot";
  }
private:
};

class Trombone : public Brass {
public:
  Trombone( unsigned size ) : Brass(size) {}
  void play() const {
    cout << "Blat";
  }
private:
};

class Violin : public String {
public:
  Violin( unsigned pitch ) : String(pitch) {}
  void play() const {
    cout << "Screech";
  }
private:
};

class Cello : public String {
public:
  Cello( unsigned pitch ) : String(pitch) {}
  void play() const {
    cout << "Squawk";
  }
private:
};

class Drum : public Percussion {
public:
  void play() const {
    cout << "Boom";
  }
private:
};

class Cymbal : public Percussion {
public:
  void play() const {
    cout << "Crash";
  }
private:
};

class MILL {
public:
  void receiveInstr( Instrument& i ) {
    Instrument* obj = &i;
    obj->makeSound();
    bool exists = false;
    // If there's a null, then insert the object
    for( size_t i = 0; i < instr.size(); i++ ) {
      if( instr[i] == NULL ) {
	instr[i] = obj;
	exists = true;
	break;
      }
    }
    // If it's not in vector, then push the object in
    if( !exists ) {
      instr.push_back( obj );
    }
  }
  Instrument* loanOut() {
    for( size_t i = 0; i < instr.size(); i++ ) {
      if( instr[i] != NULL ) {
	Instrument* obj = instr[i]; // Need to set to null later so get var
	instr[i] = NULL;
	return obj;
      }
    }
    return NULL;
  }
  void dailyTestPlay() {
    for( size_t i = 0; i < instr.size(); i++ ) {
      if( instr[i] != NULL ) {
	instr[i]->makeSound();
      }
    }
  }
private:
  vector<Instrument*> instr;
};

class Musician {
public:
  Musician() : instr( NULL ) {}
  void acceptInstr( Instrument& i ) { instr = &i; }
  Instrument* giveBackInstr( ) { 
    Instrument* tmp(instr); 
    instr = NULL;
    return tmp;
  }
  void testPlay() const {
    if( instr )
      instr->makeSound(); 
    else
      cerr << "have no instr\n";
  }
  void play() const {
    if( instr != NULL ) { // Gotta make sure this guy has an instrument
      instr->play();
    }
  }
private:
  Instrument* instr;
};

class Orch {
public:
  Orch() : muse( 25, NULL ) {}
  // Since orch is a certain size, we can only replace NULL in the orch
  void addPlayer( Musician& guy ) {
    for( size_t i = 0; i < muse.size(); i++ ) {
      if( muse[i] == NULL ) {
	muse[i] = &guy;
      }
    }
  }
  void play() const {
    for( size_t i = 0; i < muse.size(); i++ ) {
      if( muse[i] != NULL ) {
	muse[i]->play(); // Gotta make sure someone filled the orch spot
      }
    }
    cout << endl;
  }
private:
  vector<Musician*> muse;
};

// PART TWO
int main()
{
  // The initialization phase
  
  Drum drum;
  Cello cello(673);
  Cymbal cymbal;
  Trombone tbone( 4 );
  Trumpet trpt( 12 ) ;
  Violin violin( 567 ) ;
  
  MILL mill;
  mill.receiveInstr( trpt );
  mill.receiveInstr( violin );
  mill.receiveInstr( tbone );
  mill.receiveInstr( drum );
  mill.receiveInstr( cello );
  mill.receiveInstr( cymbal );
  
  Musician bob;
  Musician sue;
  Musician mary;
  Musician ralph;
  Musician jody;
  Musician morgan;
  
  Orch orch;
  
  
  
  // THE SCENARIO
  
  //Bob joins the orchestra without an instrument.
  orch.addPlayer(bob);
  
  //The orchestra performs
  cout << "orch performs\n";
  orch.play();
  
  //Sue gets an instrument from the MIL2 and joins the orchestra.
  sue.acceptInstr( *mill.loanOut() );
  orch.addPlayer(sue);
  
  //Ralph gets an instrument from the MIL2.
  ralph.acceptInstr( *mill.loanOut() );
  
  //Mary gets an instrument from the MIL2 and joins the orchestra.
  mary.acceptInstr( *mill.loanOut() );
  orch.addPlayer(mary);
  
  //Ralph returns his instrument to the MIL2.
  mill.receiveInstr( *ralph.giveBackInstr() );
  
  //Jody gets an instrument from the MIL2 and joins the orchestra.
  jody.acceptInstr( *mill.loanOut() );
  orch.addPlayer(jody);
  
  // morgan gets an instrument from the MIL2
  morgan.acceptInstr( *mill.loanOut() );
  
  //The orchestra performs.
  cout << "orch performs\n";
  orch.play();
  
  //Ralph joins the orchestra.
  orch.addPlayer(ralph);
  
  //The orchestra performs.
  cout << "orch performs\n";
  orch.play();
  
  // bob gets an instrument from the MIL2
  bob.acceptInstr( *mill.loanOut() );
  
  // ralph gets an instrument from the MIL2
  ralph.acceptInstr( *mill.loanOut() );
  
  //The orchestra performs.
  cout << "orch performs\n";
  orch.play();
  
  //Morgan joins the orchestra.
  orch.addPlayer(morgan);
  
  //The orchestra performs.
  cout << "orch performs\n";
  orch.play();
  
} // main
