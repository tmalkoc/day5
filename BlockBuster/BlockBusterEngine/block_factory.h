#pragma once
#include "pch.h"
#include "block.h"
#include "utils.h"

namespace blockbuster::engine
{
  template<typename T = double>
  using block_factory = std::function<block_unique_ptr<T>(std::istream&)>;
}

namespace
{
  using namespace blockbuster::engine;
  using namespace blockbuster::engine::utils;

  template<typename T = double>
  block_unique_ptr<T> identity_factory(std::istream&)
  {
    return std::make_unique<block<T>>([](const T& input) { return input; });
  }

  template<typename T = double>
  block_unique_ptr<T> addition_factory(std::istream& is)
  {
    return std::make_unique<block<T>>([n = read_param<T>(is, 0)](const T& input) { return input + n; });
  }

  template<typename T = double>
  block_unique_ptr<T> multiplication_factory(std::istream& is)
  {
    return std::make_unique<block<T>>([n = read_param<T>(is, 1)](const T& input) { return input * n; });
  }

  template<typename T = double>
  block_unique_ptr<T> power_factory(std::istream& is)
  {
    return std::make_unique<block<T>>([n = read_param<T>(is, 1)](const T& input)
    {
      return std::pow(input, n);
    });
  }

  template<typename T = double>
  block_unique_ptr<T> condition_factory(std::istream& is)
  {
    return std::make_unique<block<T>>([n = read_param<T>(is, 0)](const T& input)
    {
      return input < n ? -1 : n < input ? 1 : 0;
    });
  }

  template<typename T = double>
  block_unique_ptr<T> limit_factory(std::istream& is)
  {
    T a = read_param<T>(is, std::numeric_limits<T>::min());
    T b = read_param<T>(is, std::numeric_limits<T>::max());;
    return std::make_unique<block<T>>([min = std::min<T>(a, b), max = std::max<T>(a, b)](const T& input)
    {
      return
        input < min ? min :
        max < input ? max :
        input;
    });
  }

  template<typename T = double>
  const block_factory<T>* get_block_factory(const std::string& id)
  {
    static const std::map<const std::string, block_factory<T>> map =
    {
      {block_id::identity, identity_factory<T> },
      {block_id::addition, addition_factory<T>},
      {block_id::multiplication, multiplication_factory<T>},
      {block_id::power, power_factory<T>},
      {block_id::limit, limit_factory<T>},
      {block_id::condition, condition_factory<T>}
    };
    const auto it = map.find(id);
    return
      it != map.end() ?
      &it->second :
      nullptr;
  }
}

namespace blockbuster::engine
{
  template<typename T = double>
  block_unique_ptr<T> get_block(const std::string& id, std::istream& is)
  {
    const auto block_factory = get_block_factory<T>(id);
    return block_factory != nullptr ? (*block_factory)(is) : block_unique_ptr<T>();
  }

  template<typename T = double>
  block_unique_ptr<T> get_block(std::istream& is)
  {
    std::string block_id;
    is >> block_id;
    return get_block<T>(block_id, is);
  }

  template<typename T = double>
  block_unique_ptr<T> get_block(const std::string& block_definition)
  {
    std::istringstream iss(block_definition);
    return get_block<T>(iss);
  }
}
