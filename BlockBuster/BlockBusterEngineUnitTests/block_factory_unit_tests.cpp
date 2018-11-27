#include  "catch.hpp"
#include "random.h"
#include "../BlockBusterEngine/utils.h"
#include "../BlockBusterEngine/block.h"
#include "../BlockBusterEngine/blockchain_factory.h"

using namespace blockbuster::engine;
using namespace blockbuster::engine::utils;

namespace blockbuster::engine::tests
{
  TEST_CASE("block_factory - create block with empty string", "[blockbuster][engine][block_factory]")
  {
    const auto block = get_block<>("");
    REQUIRE(block == nullptr);
  }

  TEST_CASE("block_factory - create block with random garbage string", "[blockbuster][engine][block_factory]")
  {
    const auto rand_str = std::to_string(random());
    const auto block = get_block(rand_str);
    REQUIRE(block == nullptr);
  }

  TEST_CASE("block_factory - create identity block", "[blockbuster][engine][block_factory]")
  {
    const auto input = random();
    const auto block = get_block(block_id::identity);
    REQUIRE(block != nullptr);
    const auto result = (*block)(input);
    REQUIRE(result == Approx(input));
  }

  TEST_CASE("block_factory - create addition block with incomplete string", "[blockbuster][engine][block_factory]")
  {
    const auto input = random();
    const auto block = get_block(block_id::addition);
    REQUIRE(block != nullptr);
    const auto result = (*block)(input);
    REQUIRE(result == Approx(input));
  }

  TEST_CASE("block_factory - create multiplication block with incomplete string", "[blockbuster][engine][block_factory]")
  {
    const auto input = random();
    const auto block = get_block(block_id::multiplication);
    REQUIRE(block != nullptr);
    const auto result = (*block)(input);
    REQUIRE(result == Approx(input));
  }

  TEST_CASE("block_factory - create condition block with incomplete string", "[blockbuster][engine][block_factory]")
  {
    const auto input = random();
    const auto block = get_block(block_id::condition);
    REQUIRE(block != nullptr);
    const auto result = (*block)(input);
    REQUIRE(result == (input < 0 ? -1 : input > 0 ? 1 : 0));
  }

  TEST_CASE("block_factory - create power block with incomplete parameter string", "[blockbuster][engine][block_factory]")
  {
    const auto input = random();
    const auto block = get_block(block_id::power);
    REQUIRE(block != nullptr);
    const auto result = (*block)(input);
    REQUIRE(result == Approx(input));
  }

  TEST_CASE("block_factory - create identity block with too many parameters", "[blockbuster][engine][block_factory]")
  {
    const auto input = random();
    const auto block_str = stringify(block_id::identity, random(), random(), random());
    const auto block = get_block(block_str);
    REQUIRE(block != nullptr);
    const auto result = (*block)(input);
    REQUIRE(result == Approx(input));
  }

  TEST_CASE("block_factory - create addition block with too many parameters", "[blockbuster][engine][block_factory]")
  {
    const auto input = random();
    const auto param = random();
    const auto block_str = stringify(block_id::addition, param, random(), random(), random());
    const auto block = get_block(block_str);
    REQUIRE(block != nullptr);
    const auto result = (*block)(input);
    REQUIRE(result == Approx(input + param));
  }

  TEST_CASE("block_factory - create multiplication block with too many parameters", "[blockbuster][engine][block_factory]")
  {
    const auto input = random();
    const auto param = random();
    const auto block_str = stringify(block_id::multiplication, param, random(), random(), random());
    const auto block = get_block(block_str);
    REQUIRE(block != nullptr);
    const auto result = (*block)(input);
    REQUIRE(result == Approx(input * param));
  }

  TEST_CASE("block_factory - create power block with too many parameters", "[blockbuster][engine][block_factory]")
  {
    const auto input = random();
    const auto param = random();
    const auto block_str = stringify(block_id::power, param, random(), random(), random());

    const auto block = get_block(block_str);
    REQUIRE(block != nullptr);
    
    const auto result = static_cast<int>((*block)(input) * 10);
    const auto expected = static_cast<int>(std::pow(input, param) * 10);
    REQUIRE(result == expected);
  }

  TEST_CASE("block_factory - create condition block with too many parameters", "[blockbuster][engine][block_factory]")
  {
    const auto param = static_cast<int>(random());
    const auto block_str = stringify(block_id::condition, param, random(), random(), random());
    const auto block = get_block<int>(block_str);
    REQUIRE(block != nullptr);

    const auto result_less = (*block)(param - 1);
    REQUIRE(result_less == -1);

    const auto result_more = (*block)(param + 1);
    REQUIRE(result_more == 1);

    const auto result = (*block)(param);
    REQUIRE(result == 0);
  }

  TEST_CASE("block_factory - create limit block with too many parameters", "[blockbuster][engine][block_factory]")
  {
    auto param1 = random();
    auto param2 = random();
    auto input = (param1 + param2) / 2;

    auto block_str = stringify(block_id::limit, param1, param2, random(), random(), random());
    auto block = get_block(block_str);
    REQUIRE(block != nullptr);

    auto result = (*block)(input);
    REQUIRE(result == Approx(input));

    auto min = std::min(param1, param2);
    auto result_min = (*block)(min - 1);
    REQUIRE(min == Approx(result_min));

    auto max = std::max(param1, param2);
    auto result_max = (*block)(max + 1);
    REQUIRE(max == Approx(result_max));
  }
}
