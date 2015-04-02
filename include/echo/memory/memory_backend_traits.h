#pragma once

#include <echo/memory/standard_memory_backend_tag.h>
#include <echo/concept/query_type.h>
#include <echo/concept2.h>

namespace echo {
namespace memory_backend_traits {

namespace detail {
namespace memory_backend_traits {

ECHO_MAKE_TYPE_QUERIER(memory_backend_tag)

ECHO_MAKE_TYPE_QUERIER(pointer)

ECHO_MAKE_TYPE_QUERIER(const_pointer)
}
}

////////////////////////
// memory_backend_tag //
////////////////////////

template <class T>
using memory_backend_tag = typename std::conditional<
    detail::memory_backend_traits::has_memory_backend_tag<T>(),
    detail::memory_backend_traits::query_memory_backend_tag<T>,
    memory::standard_memory_backend_tag>::type;

////////////////
// value_type //
////////////////

template <class T>
using value_type = typename T::value_type;

/////////////
// pointer //
/////////////

template <class T>
using pointer =
    typename std::conditional<detail::memory_backend_traits::has_pointer<T>(),
                              detail::memory_backend_traits::query_pointer<T>,
                              value_type<T>*>::type;

///////////////////
// const_pointer //
///////////////////

template <class T>
using const_pointer = typename std::conditional<
    detail::memory_backend_traits::has_const_pointer<T>(),
    detail::memory_backend_traits::query_const_pointer<T>,
    const value_type<T>*>::type;
}
}
