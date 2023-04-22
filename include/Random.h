//
// Copyright (c) 2023 James A. Chappell (rlrrlrll@gmail.com)
//

#pragma once

#include "Generator.h"

#include <type_traits>

namespace Storage_B
{
  template<typename A> concept Arithmetic = std::is_arithmetic<A>::value;
  template<Arithmetic T> class Random
  {
  public:
    Random(T low, T high) :
      gen_(Generator::Create())
    {
      if constexpr (std::is_integral<T>::value)
      {
        dis_.in = new std::uniform_int_distribution<T>(low, high);
      }
      else if (std::is_floating_point<T>::value)
      {
        dis_.re = new std::uniform_real_distribution<T>(low, high);
      }
    }

    Random() = delete;
  
    // no copy
    Random(const Random&) = delete;
    Random(Random&&) = delete;
    Random& operator=(const Random&) = delete;

    ~Random()
    {
      if constexpr (std::is_integral<T>::value)
      {
        delete dis_.in;
      }
      else
      {
        delete dis_.re;
      }
    }

    T operator()() const
    {
      if constexpr (std::is_integral<T>::value)
      {
        return (*dis_.in)((*gen_)());
      }
      else
      {
        return (*dis_.re)((*gen_)());
      }
    }

  private:
    union 
    {
      std::uniform_int_distribution<T> *in;
      std::uniform_real_distribution<T> *re;
    } dis_;

    std::unique_ptr<Generator> gen_; 
  };
}
