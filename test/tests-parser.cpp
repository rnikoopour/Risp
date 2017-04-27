#include <memory>
#include <string>

#include "../external/catch.hpp"
#include "../parser.hpp"

SCENARIO("parser::parse parses input properly") {
  GIVEN("input is a string representing anything") {
    THEN("output should be a token::TokenType::LIST token") {
      const auto input1 = std::string("10");
      auto output1 = parser::parse(input1);
      CHECK(output1->is_list == true);
      const auto input2 = std::string("foo");
      auto output2 = parser::parse(input2);
      CHECK(output2->is_list == true);
      const auto input3 = std::string("10.10");
      auto output3 = parser::parse(input3);
      CHECK(output3->is_list == true);
      const auto input4 = std::string("\"test\"");
      auto output4 = parser::parse(input4);
      CHECK(output4->is_list == true);
    }
  }
}

SCENARIO("parser noramlizes input properly") {
  GIVEN("input has '(' and ')' in it") {
    THEN("output should add space around parens") {
      const auto input = "(foo)";
      CHECK(parser::test::normalize(input) == " ( foo ) ");
    }
  }
}

SCENARIO("parse_tokens creates tokens properly") {
  GIVEN("input is (foo)") {
    THEN("output should be a token list with identifier foo") {
      const auto expression = "(foo)";
      auto tokens = parser::test::tokenize(expression);
      auto result = parser::test::parse_tokens(tokens);
      CHECK(result->list.size() == 1);
    }
  }
  GIVEN("input is foo") {
    /* 
     * Need to revisit this test. something
     *  is incorrect with the overall behavior.
     *  For now, this is treated as expected behavior
     */
    THEN("output should be a token list with identifier foo") {
      const auto expression = "foo";
      auto tokens = parser::test::tokenize(expression);
      auto result = parser::test::parse_tokens(tokens);
      CHECK(result->list.size() == 1);
    }
  }
}
