#include <echo/memory/memory_backend_traits.h>
#include <echo/memory/simd_allocator.h>
#include <echo/test.h>

using namespace echo;
using namespace echo::memory;

struct my_memory_backend_tag {};

struct MyAlloc : SimdAllocator<double> {
  using memory_backend_tag = my_memory_backend_tag;
  using pointer = double;
};

TEST_CASE("memory_backend_traits") {
  REQUIRE(std::is_same<my_memory_backend_tag,
                       memory_backend_traits::memory_backend_tag<MyAlloc>>());
  REQUIRE(std::is_same<
      standard_memory_backend_tag,
      memory_backend_traits::memory_backend_tag<SimdAllocator<double>>>());

  REQUIRE(std::is_same<double, memory_backend_traits::pointer<MyAlloc>>());
  REQUIRE(
      std::is_same<double*,
                   memory_backend_traits::pointer<SimdAllocator<double>>>());
  REQUIRE(std::is_same<const double*, memory_backend_traits::const_pointer<
                                          SimdAllocator<double>>>());
}
