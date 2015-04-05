#include <echo/memory/simd_allocator.h>
#include <echo/memory/static_allocator.h>
#include <echo/memory/concept.h>
#include <echo/test.h>
#include <list>

using namespace echo::memory;

TEST_CASE("concept") {
  using ListIterator = std::list<int>::iterator;
  REQUIRE(concept::algorithm_iterator_copy<int*, int*, int*>());

  REQUIRE(!concept::algorithm_iterator_copy<int*, int*, const int*>());

  REQUIRE(concept::algorithm_iterator_copy<int*, int*, double*>());

  REQUIRE(concept::algorithm_iterator_copy<ListIterator, ListIterator, int*>());

  REQUIRE(concept::algorithm_iterator_memcpyable_copy<int*, int*, int*>());
  REQUIRE(!concept::algorithm_iterator_memcpyable_copy<int, int*, int*>());

  REQUIRE(!concept::algorithm_iterator_memcpyable_copy<ListIterator,
                                                       ListIterator, int*>());
}
