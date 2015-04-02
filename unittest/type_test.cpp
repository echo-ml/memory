// #include <echo/memory/type.h>
#include <echo/memory/simd_allocator.h>
#include <echo/memory/static_allocator.h>
#include <echo/test.h>

using namespace echo::memory;

struct my_memory_backend_tag {};

struct MyAlloc : SimdAllocator<double> {
  using memory_backend_tag = my_memory_backend_tag;
};

TEST_CASE("type") {
  // using Alloc1 = StaticAllocator<double>;
  // using Alloc2 = SimdAllocator<double>;
  //
  // REQUIRE(concept::memory_backend<Alloc1>());
  //
  // echo::type_equal<standard_memory_backend_tag,
  //                  type::memory_backend_tag<Alloc2>>();
  // echo::type_equal<my_memory_backend_tag, type::memory_backend_tag<MyAlloc>>();
}
