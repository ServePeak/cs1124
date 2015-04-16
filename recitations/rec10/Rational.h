#ifndef RATIONAL_H
#define RATIONAL_H
#include <iostream>

namespace CS1124 {

  class Rational {
  public:
    Rational();
    Rational( int num, int denom=1 );
    int getNum() const;
    int getDenom() const;
    friend std::istream& operator>>( std::istream& in, Rational& rat );
    friend std::ostream& operator<<( std::ostream& os, Rational& rat );
    Rational& operator+=( Rational rhs );
    bool operator==( Rational rhs );
    Rational& operator++();
    Rational operator++(int);
  private:
    int numerator;
    int denominator;
  };

  Rational& operator+( Rational lhs, const Rational& rhs );
  bool operator!=( const Rational& lhs, const Rational& rhs );

}

#endif
