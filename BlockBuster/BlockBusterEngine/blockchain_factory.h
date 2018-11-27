#pragma once
#include "pch.h"
#include "block_factory.h"

namespace blockbuster::engine
{
  template<typename T = double>
  std::vector<block_unique_ptr<T>> blockchain_factory(std::istream& is)
  {
    std::vector<block_unique_ptr<T>> result;
    std::transform(
      std::istream_iterator<std::string>(is),
      std::istream_iterator<std::string>(),
      std::back_inserter(result),
      [&is](const std::string& block_id) { return get_block(block_id, is); });

    result.erase(
      std::remove_if(result.begin(), result.end(), [](const block_unique_ptr<T>& ptr) { return ptr == nullptr; }),
      result.end());

    return result;
  }

  template<typename T = double>
  std::vector<block_unique_ptr<T>> blockchain_factory(const std::string& str)
  {
    auto iss = std::istringstream(str);
    return blockchain_factory<T>(iss);
  }
}
