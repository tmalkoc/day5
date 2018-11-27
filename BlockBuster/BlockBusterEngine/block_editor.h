#pragma once
#include "pch.h"
#include "utils.h"

namespace
{
  using namespace blockbuster::engine;

  template<typename T = double>
  std::string read_block_params(std::istream& is, unsigned count)
  {
    if (count == 0)
      return "";
    
    T param;
    is >> param;
    return param + " " +
  }

  std::string read_block(std::istream& is)
  {
    std::string block_name;
    is >> block_name;

  }
}

namespace blockbuster::engine
{
  template<typename T = double>
  std::vector<std::string> block_stream_reader(std::istream& is)
  {
    std::vector<std::string> result;
    
    std::transform(
      std::istream_iterator<std::string>(is),
      std::istream_iterator<std::string>(),
      std::back_inserter(result),
      [&is](const std::string& block_id)
    {
      return "";
    });

    return result;
  }
}
