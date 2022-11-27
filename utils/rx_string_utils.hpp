#pragma once
#include <vector>
#include <string>

using namespace std;

using std::string;
namespace rx {
  namespace strutils {
    std::vector<std::string> split(const std::string &s, const std::string &delim);
  }
}
