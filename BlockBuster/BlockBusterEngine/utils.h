#pragma once
#include "pch.h"
#include <fstream>

namespace blockbuster::engine::utils
{
  template<typename iterator>
  std::string join(
    iterator begin,
    iterator end,
    const std::string& separator)
  {
    using value_type = typename std::iterator_traits<iterator>::value_type;

    std::ostringstream oss;
    std::copy(begin, end, std::ostream_iterator<value_type>(oss, separator.c_str()));
    auto res = oss.str();
    auto size = static_cast<int>(res.size()) - static_cast<int>(separator.size());
    if (0 <= size)
      res.erase(res.begin() + size, res.end());
    return res;
  }
  template<typename T>
  T read_param(std::istream& is, const T& default_val)
  {
    T n = default_val;
    is >> n;
    return n;
  }

  template<typename T = double>
  std::string get_params_as_string(std::istream& is, unsigned count)
  {
    if (count == 0)
      return "";
    std::ostringstream oss;
    oss << read_param<T>(is, 0);
    if (1 < count)
      oss  << ' ' << get_params_as_string<T>(is, count - 1);
    return oss.str();
  }

  template<typename T>
  std::string stringify(const T& t)
  {
    std::ostringstream string_stream;
    string_stream << t;
    return string_stream.str();
  }

  template<typename T, typename ... Args>
  std::string stringify(const T& first, Args ... args)
  {
    return stringify(first) + " " + stringify(args...);
  }

  std::string trim(const std::string &);

  class string_separated_by_char
  {
  protected:
    string_separated_by_char(char separator) : separator_(separator) {}

  public: 
    virtual  ~string_separated_by_char() = default;
    operator std::string() const { return str_; }
    const char separator_;

  private:
    std::string str_;

    friend std::istream& operator>>(std::istream& is, string_separated_by_char& result)
    {
      return std::getline(is, result.str_, result.separator_);
    }
  };

  class string_separated_by_newline final : public string_separated_by_char
  {
  public:
    explicit string_separated_by_newline()
      : string_separated_by_char('\n')
    { }
  };

  class string_separated_by_semicolon final : public string_separated_by_char
  {
  public:
    explicit string_separated_by_semicolon()
      : string_separated_by_char(';')
    { }
  };

  class string_separated_by_comma final : public string_separated_by_char
  {
  public:
    explicit string_separated_by_comma()
      : string_separated_by_char(',')
    { }
  };
}
