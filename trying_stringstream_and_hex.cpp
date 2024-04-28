#include <iostream>
#include <sstream>
#include <ios>

int main() {
  std::stringstream ss;
  ss<<std::hex<<42;
  std::string res(ss.str());
  std::cout<<res<<std::endl;
  ss.str("");
  ss<<std::hex<<36;
  std::cout<<(ss.str())<<std::endl;
  return 0;
}