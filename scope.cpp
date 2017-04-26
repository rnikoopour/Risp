#ifndef SCOPE
#define SCOPE

#include "scope.hpp"

namespace scope {
  Scope::Scope() {
    current["x"] = token::create_token("10");
  };
  Scope::Scope(UniqueScopePointer parent) : parent(std::move(parent)) {};
  
  token::UniqueTokenPointer search_scope(UniqueScopePointer& scope, const std::string& symbol) {
    auto search_result = scope->current.find(symbol);
    if (search_result != scope->current.end()) {
      return token::create_token(search_result->second->value);
    }
    return token::create_token("Symbol not found");
  }
}
#endif
