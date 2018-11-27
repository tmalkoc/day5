#pragma once
#include "pch.h"
#include "utils.h"

namespace  blockbuster::engine
{
  template<typename T = double>
  std::vector<std::string> blockchain_editor_factory(std::istream& is)
  {
    std::vector<std::string> blocks_strings;
    std::copy(
      std::istream_iterator<utils::string_separated_by_semicolon>(is),
      std::istream_iterator<utils::string_separated_by_semicolon>(),
      std::back_inserter(blocks_strings));

    return blocks_strings;
  }

  template<typename T = double>
  std::vector<std::string> blockchain_editor_factory(const std::string& str)
  {
    auto iss = std::istringstream(str);
    return blockchain_editor_factory<T>(iss);
  }
}