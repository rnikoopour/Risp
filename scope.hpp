#ifndef SCOPE_HPP
#define SCOPE_HPP

#include <map>
#include <memory>
#include <string>

#include "token.hpp"

namespace scope {
  typedef std::map<std::string, token::UniqueTokenPointer> ScopeType;
  struct Scope {
    ScopeType current = {};
    std::unique_ptr<Scope> parent = std::make_unique<Scope>(nullptr);
    Scope();
    Scope(std::unique_ptr<Scope> parent);
  };
  typedef std::unique_ptr<Scope> UniqueScopePointer;
  token::UniqueTokenPointer search_scope(UniqueScopePointer& scope, const std::string& symbol);
  inline auto create_scope() { return std::make_unique<Scope>(); }
}
#endif
