#include "catch.hpp"
#include <vector>
#include "random.h"
#include "../BlockBusterEngine/block.h"
#include "../BlockBusterEngine/blockchain_factory.h"
#include "../BlockBusterEngine/blockchain_cruncher.h"

using namespace blockbuster::engine;

namespace blockbuster::engine::tests
{
  TEST_CASE("blockchain_cruncher - empty block chain", "[blockbuster][engine][blockchain_cruncher]")
  {
    const auto input = random();
    std::vector<std::unique_ptr<block<>>> v;
    auto res = blockchain_cruncher(v.begin(), v.end(), input);
    REQUIRE(res == input);
  }

  TEST_CASE("blockchain_cruncher - block chain with nulls", "[blockbuster][engine][blockchain_cruncher]")
  {
    const auto input = random();
    std::vector<std::unique_ptr<block<>>> v;
    v.push_back(std::unique_ptr<block<>>());
    v.push_back(std::unique_ptr<block<>>());
    v.push_back(std::unique_ptr<block<>>());
    auto res = blockchain_cruncher(v.begin(), v.end(), input);
    REQUIRE(res == input);
  }

  TEST_CASE("blockchain_cruncher - block chain with single addition block", "[blockbuster][engine][blockchain_cruncher]")
  {
    const auto input = random();
    auto chain = blockchain_factory("limit 5 5 addition 2 addition 3 multiplication 2 power 2");
    auto res = blockchain_cruncher(chain.begin(), chain.end(), input);
    REQUIRE(res == std::pow((5 + 2 + 3) * 2, 2));
  }

  TEST_CASE("blockchain_cruncher - block chain with single addition block and some garbage", "[blockbuster][engine][blockchain_cruncher]")
  {
    const auto input = random();

    auto chain = blockchain_factory("limit 5 5 garbage 2 addition garbage 2 addition 3 garbage multiplication 2");
    auto res = blockchain_cruncher(chain.begin(), chain.end(), input);

    REQUIRE(res == 5);
  }
}