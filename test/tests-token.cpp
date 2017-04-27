#include <memory>
#include <string>

#include "../external/catch.hpp"
#include "../token.hpp"

unsigned int Factorial( unsigned int number ) {
  return number <= 1 ? number : Factorial(number-1)*number;
}

SCENARIO("token::disover_type discovers token types properly") {
  GIVEN("value is a string representing an integer") {
    THEN("it should return token::TokenType::INTEGER") {
      auto value = std::string("10");
      CHECK(token::discover_type(value) == token::TokenType::INTEGER);
    }
  }

  GIVEN("value is a string representing an float") {
    THEN("it should return token::TokenType::FLOAT") {
      auto value = std::string("10.2");
      CHECK(token::discover_type(value) == token::TokenType::FLOAT);
    }
  }

  GIVEN("value is a string representing an string") {
    THEN("it should return token::TokenType::STRING") {
      auto value = std::string("\"I am a string\"");
      CHECK(token::discover_type(value) == token::TokenType::STRING);
    }
  }

  GIVEN("value is a string representing an identifier") {
    THEN("it should return token::TokenType::IDENTIFIER") {
      auto value = std::string("identifier");
      CHECK(token::discover_type(value) == token::TokenType::IDENTIFIER);
    }
  }
}

SCENARIO("token::Token constructs properly") {
  GIVEN("constructor is called with a std::string") {
    THEN("a token should be constructed properly") {
      auto token = new token::Token(std::string("foo"));
      CHECK(token->value == "foo");
      CHECK(token->is_list == false);
      CHECK(token->type == token::TokenType::IDENTIFIER);
      CHECK(token->list.size() == 0);
    }
  }
  GIVEN("constructor is called with a char*") {
    THEN("a token should be constructed properly") {
      auto token = new token::Token("foo");
      CHECK(token->value == "foo");
      CHECK(token->is_list == false);
      CHECK(token->type == token::TokenType::IDENTIFIER);
      CHECK(token->list.size() == 0);
    }
  }

  GIVEN("constructor is called with true") {
    THEN("a token should be constructed properly") {
      auto token = new token::Token(true);
      CHECK(token->value == "__RISP_THIS_SHOULD_NEVER_PRINT__");
      CHECK(token->is_list == true);
      CHECK(token->type == token::TokenType::LIST);
      CHECK(token->list.size() == 0);
    }
  }
}

SCENARIO("token::create_token works properly") {
   GIVEN("token::create_token is called with a std::string") {
    THEN("a token should be created properly") {
      auto token = token::create_token(std::string("foo"));
      CHECK(token->value == "foo");
      CHECK(token->is_list == false);
      CHECK(token->type == token::TokenType::IDENTIFIER);
      CHECK(token->list.size() == 0);
    }
  }
  GIVEN("token::create_token is called with a char*") {
    THEN("a token should be created properly") {
      auto token = token::create_token("foo");
      CHECK(token->value == "foo");
      CHECK(token->is_list == false);
      CHECK(token->type == token::TokenType::IDENTIFIER);
      CHECK(token->list.size() == 0);
    }
  }

  GIVEN("token::create_token is called with true") {
    THEN("a token should be created properly") {
      auto token = token::create_token(true);
      CHECK(token->value == "__RISP_THIS_SHOULD_NEVER_PRINT__");
      CHECK(token->is_list == true);
      CHECK(token->type == token::TokenType::LIST);
      CHECK(token->list.size() == 0);
    }
  }
}
