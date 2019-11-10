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
        _dis.in = new std::uniform_int_distribution<T>(low, high);
      }
      else if (std::is_floating_point<T>::value)
      {
        _dis.re = new std::uniform_real_distribution<T>(low, high);
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
        delete _dis.in;
      }
      else
      {
        delete _dis.re;
      }
    }

    T operator()()
    {
      if constexpr (std::is_integral<T>::value)
      {
        return (*_dis.in)(_gen->get());
      }
      else if (std::is_floating_point<T>::value)
      {
        return (*_dis.re)(_gen->get());
      }
    }

  private:
    union 
    {
      std::uniform_int_distribution<T> *in;
      std::uniform_real_distribution<T> *re;
    } _dis;

    std::shared_ptr<Generator> _gen; 
  };
}
