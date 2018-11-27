#include  "catch.hpp"
#include <string>
#include <sstream>
#include <iterator>
#include <algorithm>
#include "../BlockBusterEngine/utils.h"

using namespace std::string_literals;

namespace blockbuster::engine::utils::tests
{
  TEST_CASE("join", "[blockbuster][utils][join]")
  {
    auto str = "Some text to join";
    auto iss = std::istringstream(str);
    auto res = join(
      std::istream_iterator<std::string>(iss), 
      std::istream_iterator<std::string>(), 
      " ");
    REQUIRE(res == str);
  }

  TEST_CASE("get_params_as_string", "[blockbuster][utils]")
  {
    auto str = "2 3.14"s;
    auto iss = std::istringstream(str);
    auto params = get_params_as_string<double>(iss, 2);
    REQUIRE(params == str);
  }

  TEST_CASE("get_params_as_string less params required than there is in the input stream", "[blockbuster][utils]")
  {
    auto str = ".02 3.14 100 .1"s;
    auto iss = std::istringstream(str);
    auto params = get_params_as_string<double>(iss, 2);
    REQUIRE(params == "0.02 3.14");
  }

  TEST_CASE("get_params_as_string more params required than there is in the input stream", "[blockbuster][utils]")
  {
    auto str = "2 3.14"s;
    auto iss = std::istringstream(str);
    auto params = get_params_as_string<double>(iss, 3);
    REQUIRE(params == str + " 0");
  }
}
