#pragma once

#include <echo/memory/concept.h>

namespace echo {
namespace memory {

namespace detail {
namespace type {

// template <class MemoryBackend, bool HasMemoryBackendTag, bool IsMemoryBackend>
// struct memory_backend_tag {};
//
// template <class MemoryBackend>
// struct memory_backend_tag<MemoryBackend, false, true> {
//   using type = standard_memory_backend_tag;
// };
//
// template <class MemoryBackend>
// struct memory_backend_tag<MemoryBackend, true, true> {
//   using type = typename MemoryBackend::memory_backend_tag;
// };
//
// CONCEPT(has_memory_backend_tag) {
//   template <class MemoryBackend>
//   auto require(const MemoryBackend&)
//       ->valid<has_type<typename MemoryBackend::memory_backend_tag> >;
// };

} //end namespace type
} //end namespace detail

namespace type {

// template <class MemoryBackend>
// using memory_backend_tag = typename detail::type::memory_backend_tag<
//     MemoryBackend,
//     static_cast<bool>(detail::type::has_memory_backend_tag<MemoryBackend>()),
//     static_cast<bool>(concept::memory_backend<MemoryBackend>())>::type;

} //end namespace type

} //end namespace memory
} //end namespace echo
