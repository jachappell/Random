#include "Generator.h"

namespace
{
  using namespace Storage_B;

  class GeneratorImpl : public Generator
  {
  public:
    GeneratorImpl() = default;

    GeneratorImpl(const GeneratorImpl&) = delete;
    GeneratorImpl& operator=(const GeneratorImpl&) = delete;

    virtual ~GeneratorImpl() = default;

    virtual std::mt19937_64& operator()() const
    {
      return _gen;
    }
  
  private:
    static std::mt19937_64 _gen;
  };

  std::mt19937_64 GeneratorImpl::_gen = std::mt19937_64(std::random_device{}());
}

std::unique_ptr<Generator> Storage_B::Generator::Create()
{
  return std::move(std::make_unique<GeneratorImpl>());
}
