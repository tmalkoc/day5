#pragma once
#include "pch.h"
#include "block.h"

namespace blockbuster::engine
{
  template<typename iterator, typename T = double>
  T blockchain_cruncher(const iterator begin, const iterator end, const T input)
  {
    return std::accumulate(begin, end, input, [](const T& input, const std::unique_ptr<block<T>>& func)
    {
      return func != nullptr ? (*func)(input) : input;
    });
  }
}
