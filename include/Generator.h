//
// Copyright (c) 2023 James A. Chappell (rlrrlrll@gmail.com)
//

#pragma once

#include <random>
#include <memory>

namespace Storage_B
{
  class Generator
  {
  public:
    Generator() = default;

    Generator(const Generator&) = delete;
    Generator& operator=(const Generator&) = delete;

    virtual ~Generator() = default;

    virtual std::mt19937_64& operator()() const = 0;
   
    static std::unique_ptr<Generator> Create();
  };
}
