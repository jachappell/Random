//
// Copyright (c) 2019 James A. Chappell (rlrrlrll@gmail.com)
//

#pragma once

#include "Generator.h"

#include <type_traits>

namespace Storage_B
{
  template<typename T> class Random
  {
  public:
    Random(T low, T high) :
      _gen(Generator::Create())
    {
      if constexpr (std::is_integral<T>::value)
      {
        _int_dis = new std::uniform_int_distribution<T>(low, high);
      }
      else if (std::is_floating_point<T>::value)
      {
        _real_dis = new std::uniform_real_distribution<T>(low, high);
      }
    }

    Random() = delete;
  
    // no copy
    Random(const Random&) = default;
    Random& operator=(const Random&) = default;

    ~Random()
    {
      if constexpr (std::is_integral<T>::value)
      {
        delete _int_dis;
      }
      else
      {
        delete _real_dis;
      }
    }

    T operator()()
    {
      if constexpr (std::is_integral<T>::value)
      {
        return (*_int_dis)(_gen->get());
      }
      else if (std::is_floating_point<T>::value)
      {
        return (*_real_dis)(_gen->get());
      }
    }

  private:
    std::uniform_int_distribution<T> * _int_dis;
    std::uniform_real_distribution<T> * _real_dis;

    std::shared_ptr<Generator> _gen; 
  };
}
