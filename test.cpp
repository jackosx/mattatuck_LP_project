

#include <iostream>
#include "src/db.h"
#include <string>

int main()
{
  std::string test = checkContact("1784CM");
  std::string test2 = checkContact("fda");
  std::cout << test << std::endl;
  std::cout << test2 << std::endl;
}
