#include "Rational.h"
#include <string>
#include <iostream>
using namespace std;

namespace CS1124 {

  Rational::Rational() {}
  Rational::Rational( int num, int denom ) : numerator(num), denominator(denom) {}

  int greatestCommonDivisor(int x, int y) {
    while (y != 0) {
      int temp = x % y;
      x = y;
      y = temp;
    }
    return x;
  }

  int Rational::getNum() const {
    return numerator;
  }

  int Rational::getDenom() const {
    return denominator;
  }
  
  istream& operator>>( istream& in, Rational& rat ) {
    int num, denom, gcd; 
    char slash;
    in >> num >> slash >> denom;
    if( num < 0 && denom < 0 ) {
      num *= -1;
      denom *= -1;
    }
    gcd = greatestCommonDivisor( num, denom );
    num /= gcd;
    denom /= gcd;
    rat.numerator = num;
    rat.denominator = denom;
  }

  ostream& operator<<( ostream& os, Rational& rat ) {
    os << rat.numerator << '/' << rat.denominator;
    return os;
  }

  Rational& Rational::operator+=( Rational rhs ) {
    int gcd;
    numerator = ( numerator * rhs.denominator ) + ( rhs.numerator * denominator );
    denominator = denominator * rhs.denominator;
    gcd = greatestCommonDivisor( numerator, denominator );
    numerator /= gcd;
    denominator /= gcd;
    return *this;
  }

  Rational& operator+( Rational lhs, const Rational& rhs ) {
    return lhs += rhs;
  }

  bool Rational::operator==( Rational rhs ) {
    return( numerator == rhs.numerator && denominator == rhs.denominator );
  }

  bool operator!=( const Rational& lhs, const Rational& rhs ) {
    return( lhs.getNum() != rhs.getNum() && lhs.getDenom() != rhs.getDenom() );
  }

  Rational& Rational::operator++() {
    numerator += denominator;
    return *this;
  }

  Rational Rational::operator++(int dummy) {
    Rational temp(*this);
    operator++();
    return temp;
  }

}
