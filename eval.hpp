#ifndef EVAL_HPP
#define EVAL_HPP

#include <algorithm>
#include <functional>
#include <map>
#include <memory>
#include <sstream>
#include <string>

#include "token.hpp"

namespace risp_eval {
  token::UniqueTokenPointer eval(token::UniqueTokenPointer& token);
}
#endif
