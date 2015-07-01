#pragma once

#define DETAIL_NS detail_concept

#include <echo/memory/memory_backend_tag.h>
#include <echo/memory/static_allocator.h>
#include <echo/memory/memory_backend_traits.h>
#include <echo/concept.h>

namespace echo {
namespace memory {

namespace concept {

using echo::concept::allocator;

//------------------------------------------------------------------------------
// static_allocator
//------------------------------------------------------------------------------
namespace DETAIL_NS {
struct StaticAllocator : Concept {
  template <class T>
  auto require(T && ) -> list<valid<typename T::template buffer_type<1>>()>;
};
}  // end namespace detail

template <class T>
constexpr bool static_allocator() {
  return models<DETAIL_NS::StaticAllocator, T>();
}

//------------------------------------------------------------------------------
// memory_backend_tag
//------------------------------------------------------------------------------
template <class T>
constexpr bool memory_backend_tag() {
  return std::is_base_of<echo::memory::memory_backend_tag, T>();
}

//------------------------------------------------------------------------------
// memory_backend
//------------------------------------------------------------------------------
namespace DETAIL_NS {
struct MemoryBackend : Concept {
  template <class T>
  auto require(T && ) -> list<
      static_allocator<T>() || allocator<T>(),
      memory_backend_tag<memory_backend_traits::memory_backend_tag<T>>()>;
};
}  // namespace detail

template <class T>
constexpr bool memory_backend() {
  return static_allocator<T>() || allocator<T>();
}

//------------------------------------------------------------------------------
// algorithm_iterator_copy
//------------------------------------------------------------------------------
namespace DETAIL_NS {
struct AlgorithmIteratorCopy : Concept {
  template <class SourceIteratorFirst, class SourceIteratorLast,
            class DestinationIteratorFirst>
  auto require(SourceIteratorFirst&& source_first,
               SourceIteratorLast&& source_last,
               DestinationIteratorFirst&& destination_first)
      -> list<echo::concept::input_iterator<SourceIteratorFirst>(),
              echo::concept::input_iterator<SourceIteratorLast>(),
              echo::concept::equality_comparable<SourceIteratorFirst,
                                                 SourceIteratorLast>(),
              echo::concept::output_iterator<DestinationIteratorFirst>(),
              valid<decltype(*destination_first = *source_first)>()>;
};
}  // namespace detail

template <class SourceIteratorFirst, class SourceIteratorLast,
          class DestinationIteratorFirst>
constexpr bool algorithm_iterator_copy() {
  return models<DETAIL_NS::AlgorithmIteratorCopy, SourceIteratorFirst,
                SourceIteratorLast, DestinationIteratorFirst>();
}

//------------------------------------------------------------------------------
// algorithm_iterator_memcpyable_copy
//------------------------------------------------------------------------------
namespace DETAIL_NS {
struct AlgorithmIteratorMemcpyableCopy : Concept {
  template <class SourceIteratorFirst, class SourceIteratorLast,
            class DestinationIteratorFirst>
  auto require(
      SourceIteratorFirst&&, SourceIteratorLast&&, DestinationIteratorFirst && )
      -> list<
          algorithm_iterator_copy<SourceIteratorFirst, SourceIteratorLast,
                                  DestinationIteratorFirst>(),

          echo::concept::contiguous_iterator<SourceIteratorFirst>(),
          echo::concept::contiguous_iterator<SourceIteratorLast>(),
          echo::concept::contiguous_iterator<DestinationIteratorFirst>(),

          same<iterator_traits::value_type<SourceIteratorFirst>,
               iterator_traits::value_type<SourceIteratorLast>>(),
          same<iterator_traits::value_type<SourceIteratorFirst>,
               iterator_traits::value_type<DestinationIteratorFirst>>(),

          std::is_pod<iterator_traits::value_type<SourceIteratorFirst>>::value>;
};
}  // namespace detail

template <class SourceIteratorFirst, class SourceIteratorLast,
          class DestinationIteratorFirst>
constexpr bool algorithm_iterator_memcpyable_copy() {
  return models<DETAIL_NS::AlgorithmIteratorMemcpyableCopy, SourceIteratorFirst,
                SourceIteratorLast, DestinationIteratorFirst>();
}

}  // end namespace concept

}  // end namespace memory
}  // end namespace echo

#undef DETAIL_NS
