#pragma once

#define DETAIL_NS detail_memory_backend_traits

#include <echo/memory/memory_backend_tag.h>
#include <echo/concept/query_type.h>
#include <echo/concept.h>

namespace echo {
namespace memory_backend_traits {

namespace DETAIL_NS {
ECHO_MAKE_TYPE_QUERIER(memory_backend_tag)

ECHO_MAKE_TYPE_QUERIER(pointer)

ECHO_MAKE_TYPE_QUERIER(const_pointer)
}  // namespace detail

//------------------------------------------------------------------------------
// memory_backend_tag
//------------------------------------------------------------------------------
template <class T>
using memory_backend_tag =
    typename std::conditional<DETAIL_NS::has_memory_backend_tag<T>(),
                              DETAIL_NS::query_memory_backend_tag<T>,
                              echo::memory::memory_backend_tag>::type;

//------------------------------------------------------------------------------
// value_type
//------------------------------------------------------------------------------
template <class T>
using value_type = typename T::value_type;

//------------------------------------------------------------------------------
// pointer
//------------------------------------------------------------------------------
template <class T>
using pointer = typename std::conditional<DETAIL_NS::has_pointer<T>(),
                                          DETAIL_NS::query_pointer<T>,
                                          value_type<T>*>::type;

//------------------------------------------------------------------------------
// const_pointer
//------------------------------------------------------------------------------
template <class T>
using const_pointer =
    typename std::conditional<DETAIL_NS::has_const_pointer<T>(),
                              DETAIL_NS::query_const_pointer<T>,
                              const value_type<T>*>::type;
}  // namespace memory_backend_traits
}  // namespace echo

#undef DETAIL_NS
