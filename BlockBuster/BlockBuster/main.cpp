#include "pch.h"
#include "../BlockBusterEngine/blockchain_factory.h"
#include "../BlockBusterEngine/blockchain_cruncher.h"
#include "../BlockBusterEngine/utils.h"

template<typename iterator>
std::vector<block_unique_ptr<double>> command_line_parser(iterator begin, iterator end);

int main(int argc, char *argv[])
{
  const auto blockchain = command_line_parser(argv, argv + argc);
  if (blockchain.size() == 0)
  {
    std::cerr << argv[0] << " --help" << std::endl;
    return -1;
  }

  std::transform(
    std::istream_iterator<double>(std::cin),
    std::istream_iterator<double>(),
    std::ostream_iterator<std::string>(std::cout),
    [&blockchain](double input)
    {
      std::ostringstream oss; 
      oss << blockbuster::engine::blockchain_cruncher(blockchain.begin(), blockchain.end(), input) << std::endl;
      return oss.str();
    });
  
  return 0;
}

std::ostream& to_help_string(std::ostream& os, const std::map<std::string, int>& map, const std::string& prefix)
{
  std::for_each(map.begin(), map.end(), [&os, &prefix](const std::pair<std::string, int>& p)
  {
    os << prefix << p.first << " (" << p.second << " parameter" << (p.second != 1 ? "s)" : ")") << std::endl;
  });
  return os;
}

std::vector<block_unique_ptr<double>> print_help(const std::string& app_name)
{
  std::cout << app_name << " [OPTIONS]" << std::endl;
  std::cout << std::endl;
  std::cout << "OPTIONS:" << std::endl;
  std::cout << "\t-h --help\t\t\tprint this help" << std::endl;
  std::cout << "\t-f --file file_name\t\tenter block chain file 'file_name'" << std::endl;
  std::cout << "\tblock chain definition in command line. Available blocks are:" << std::endl;
  to_help_string(std::cout, block_id::blocks, "\t- ") << std::endl;
  std::cout << std::endl;
  std::cout << "Examples:" << std::endl;
  std::cout << "\t$ " << app_name << " limit 5 5 addition 2 addition 3 multiplication 2 power 2" << std::endl;
  std::cout << "\t$ " << app_name << " limit 5 5 addition 2 addition 3 multiplication 2 power 2 < input_values > output_values" << std::endl;
  std::cout << "\t$ " << app_name << " -f blocks < input_values > output_values" << std::endl;
  std::cout << "\t$ " << app_name << " -f blocks < input_values" << std::endl;

  return std::vector<block_unique_ptr<double>>();
}

template<typename iterator>
std::vector<block_unique_ptr<double>> from_file(iterator begin, iterator end)
{
  if (++begin == end)
  {
    std::cerr << "file name expected" << std::endl;
    return std::vector<block_unique_ptr<double>>();
  }
  std::ifstream is{ std::string(*begin) };
  return blockbuster::engine::blockchain_factory<double>(is);
}

template<typename iterator>
std::vector<block_unique_ptr<double>> command_line_parser(iterator begin, iterator end)
{
  const auto app_name = std::string(*(begin++));
  if (begin == end)
    return std::vector<block_unique_ptr<double>>();

  const auto first_arg = std::string(*begin);
  if (first_arg == "-h" || first_arg == "--help")
    return print_help(app_name);
  if (first_arg == "-f" || first_arg == "--file")
    return from_file(begin, end);
  return blockbuster::engine::blockchain_factory<double>(utils::join(begin, end, " "));
}

