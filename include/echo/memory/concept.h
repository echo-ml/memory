#pragma once

#include <echo/memory/static_allocator.h>
#include <echo/concept2.h>

namespace echo {
namespace memory {

namespace concept {

using echo::concept::allocator;

//////////////////////
// static_allocator //
//////////////////////

namespace detail { namespace concept {

struct StaticAllocator : Concept {
  template<class T>
  auto require(T &&)->list<
      valid<typename T::template buffer_type<1>>()
  >;
};

} //end namespace concept
} //end namespace detail

template<class T>
constexpr bool static_allocator() {
  return models<detail::concept::StaticAllocator, T>();
}

////////////////////
// memory_backend //
////////////////////

template<class T>
constexpr bool memory_backend() {
  return static_allocator<T>() || allocator<T>();
}

// CONCEPT(memory_backend) {
//   template <class T>
//   auto require(T)->valid<is_true_c<allocator<T>() || static_allocator<T>()> >;
// };

}  // end namespace concept

}  // end namespace memory
}  // end namespace echo
