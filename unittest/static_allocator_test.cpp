#include <echo/memory/static_allocator.h>
#include <echo/test.h>

using namespace echo::memory;

TEST_CASE("static_allocator") {
  using Allocator = StaticAllocator<double, 64>;
  Allocator::buffer_type<5> buffer;
  REQUIRE((reinterpret_cast<long>(buffer.data()) % 64l) == 0);
  REQUIRE(sizeof(buffer) >= 5*sizeof(double));
  // REQUIRE(concept::is_static_allocator<Allocator>());
  // REQUIRE(concept::is_allocator<Allocator>());
}
