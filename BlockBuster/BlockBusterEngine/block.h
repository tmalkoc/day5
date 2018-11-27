#pragma once
#include "pch.h"

namespace blockbuster::engine
{
  template<typename T = double>
  using block = std::function<T(T)>;

  template<typename T = double>
  using block_unique_ptr = std::unique_ptr<block<T>>;

  class block_id final
  {
  public:
    inline static const std::string identity = "identity";
    inline static const std::string addition = "addition";
    inline static const std::string multiplication = "multiplication";
    inline static const std::string power = "power";
    inline static const std::string limit = "limit";
    inline static const std::string condition = "condition";

    inline static const std::map<std::string, int> blocks = 
    {
      {identity, 0}, {addition, 1}, {multiplication, 1}, {power, 1}, {condition, 1}, {limit,2}
    };
  };
}
