#include "Random.h"

#include <iostream>
#include <iomanip>

using namespace Storage_B;

int main()
{

  auto num = 10u;

  auto die = Random<unsigned short>(1, 6);
  std::cout << "Simulate " << num <<  " dice (die) rolls:" << std::endl;
  for (auto i = 0u ; i < num ; i++)
  {
    std::cout << "Roll " << std::setfill(' ') << std::setw(2) << i + 1  << ": "
              << die() << std::endl;
  }

  auto min = -1.0;
  auto max = 1.0;

  auto ran = Random<float>(min, max);
  std::cout << "\nGenerate " << num << " random numbers between "
            << min << " and " << max << ":" << std::endl;

  for (auto i = 0u ; i < num ; i++)
  {
    std::cout << ran() << std::endl;
  }

  return 0 ;
}
