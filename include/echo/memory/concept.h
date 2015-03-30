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

CONCEPT(static_allocator) {
  template <class T>
  auto require(T alloc)->valid<has_type<typename T::template buffer_type<1>>>;
};

////////////////////
// memory_backend //
////////////////////

CONCEPT(memory_backend) {
  template <class T>
  auto require(T)->valid<is_true_c<allocator<T>() || static_allocator<T>()> >;
};

}  // end namespace concept

}  // end namespace memory
}  // end namespace echo
