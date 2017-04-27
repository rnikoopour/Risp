#include "../external/catch.hpp"

unsigned int Factorial( unsigned int number ) {
  return number <= 1 ? number : Factorial(number-1)*number;
}

SCENARIO("foo", "[bar]") {
  GIVEN( "BAZ" ) {
    WHEN("BOO") {
      REQUIRE( Factorial(1) == 1 );
      REQUIRE( Factorial(2) == 2 );
    }
  }
}

SCENARIO("@") {
  GIVEN( "fdasf" ) {
    WHEN("asdfa") {
      REQUIRE( Factorial(1) == 1 );
      REQUIRE( Factorial(2) == 2 );
      REQUIRE( Factorial(2) == 2 );
      REQUIRE( Factorial(2) == 2 );
      REQUIRE( Factorial(2) == 2 );
      REQUIRE( Factorial(2) == 2 );
      REQUIRE( Factorial(2) == 2 );
				    
    }
  }
}

