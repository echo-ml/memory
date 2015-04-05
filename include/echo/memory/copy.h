#pragma once

#include <algorithm>
#include <echo/memory/concept.h>
#include <echo/memory/operation.h>

namespace echo {
namespace memory {

//////////
// copy //
//////////

// single memory backend
template <class MemoryBackendTag, class IteratorSourceFirst,
          class IteratorSourceLast, class IteratorDestinationFirst,
          CONCEPT_REQUIRES(concept::memory_backend_tag<MemoryBackendTag>() &&
                           concept::algorithm_iterator_memcpyable_copy<
                               IteratorSourceFirst, IteratorSourceLast,
                               IteratorDestinationFirst>())>
void copy(MemoryBackendTag, IteratorSourceFirst source_first,
          IteratorSourceLast source_last,
          IteratorDestinationFirst destination_first, overload::choice<0>) {
  auto destination_first_address =
      reinterpret_cast<unsigned char*>(std::addressof(*destination_first));
  auto source_first_address =
      reinterpret_cast<const unsigned char*>(std::addressof(*source_first));
  auto source_last_address =
      reinterpret_cast<const unsigned char*>(std::addressof(*source_last));
  memcpy(MemoryBackendTag(), static_cast<void*>(destination_first_address),
         static_cast<const void*>(source_first_address),
         std::distance(source_first_address, source_last_address));
}

template <
    class IteratorSourceFirst, class IteratorSourceLast,
    class IteratorDestinationFirst,
    CONCEPT_REQUIRES(concept::algorithm_iterator_copy<
        IteratorSourceFirst, IteratorSourceLast, IteratorDestinationFirst>())>
void copy(memory_backend_tag, IteratorSourceFirst source_first,
          IteratorSourceLast source_last,
          IteratorDestinationFirst destination_first, overload::choice<1>) {
  std::copy(source_first, source_last, destination_first);
}

template <class MemoryBackendTag, class IteratorSourceFirst,
          class IteratorSourceLast, class IteratorDestinationFirst,
          CONCEPT_REQUIRES(concept::memory_backend_tag<MemoryBackendTag>() &&
                           concept::algorithm_iterator_memcpyable_copy<
                               IteratorSourceFirst, IteratorSourceLast,
                               IteratorDestinationFirst>())>
void copy(MemoryBackendTag, IteratorSourceFirst source_first,
          IteratorSourceLast source_last,
          IteratorDestinationFirst destination_first) {
  copy(MemoryBackendTag(), source_first, source_last, destination_first,
       overload::selector());
}

// two memory backends
template <class SourceMemoryBackendTag, class DestinationMemoryBackendTag,
          class IteratorSourceFirst, class IteratorSourceLast,
          class IteratorDestinationFirst,
          CONCEPT_REQUIRES(
              concept::memory_backend_tag<SourceMemoryBackendTag>() &&
              concept::memory_backend_tag<DestinationMemoryBackendTag>() &&
              concept::algorithm_iterator_memcpyable_copy<
                  IteratorSourceFirst, IteratorSourceLast,
                  IteratorDestinationFirst>())>
void copy(SourceMemoryBackendTag, IteratorSourceFirst source_first,
          IteratorSourceLast source_last, DestinationMemoryBackendTag,
          IteratorDestinationFirst destination_first, overload::choice<0>) {
  auto destination_first_address =
      reinterpret_cast<unsigned char*>(std::addressof(*destination_first));
  auto source_first_address =
      reinterpret_cast<const unsigned char*>(std::addressof(*source_first));
  auto source_last_address =
      reinterpret_cast<const unsigned char*>(std::addressof(*source_last));
  memcpy(DestinationMemoryBackendTag(),
         static_cast<void*>(destination_first_address),
         SourceMemoryBackendTag(),
         static_cast<const void*>(source_first_address),
         std::distance(source_first_address, source_last_address));
}

template <
    class IteratorSourceFirst, class IteratorSourceLast,
    class IteratorDestinationFirst,
    CONCEPT_REQUIRES(concept::algorithm_iterator_memcpyable_copy<
        IteratorSourceFirst, IteratorSourceLast, IteratorDestinationFirst>())>
void copy(memory_backend_tag, IteratorSourceFirst source_first,
          IteratorSourceLast source_last, memory_backend_tag,
          IteratorDestinationFirst destination_first, overload::choice<1>) {
  copy(memory_backend_tag(), source_first, source_last, destination_first);
}

template <class MemoryBackendTag, class IteratorSourceFirst,
          class IteratorSourceLast, class IteratorDestinationFirst,
          CONCEPT_REQUIRES(concept::memory_backend_tag<MemoryBackendTag>() &&
                           concept::algorithm_iterator_copy<
                               IteratorSourceFirst, IteratorSourceLast,
                               IteratorDestinationFirst>())>
void copy(MemoryBackendTag, IteratorSourceFirst source_first,
          IteratorSourceLast source_last, MemoryBackendTag,
          IteratorDestinationFirst destination_first, overload::choice<0>) {
  copy(MemoryBackendTag(), source_first, source_last, destination_first);
}

template <class SourceMemoryBackendTag, class DestinationMemoryBackendTag,
          class IteratorSourceFirst, class IteratorSourceLast,
          class IteratorDestinationFirst,
          CONCEPT_REQUIRES(
              concept::memory_backend_tag<SourceMemoryBackendTag>() &&
              concept::memory_backend_tag<DestinationMemoryBackendTag>() &&
              concept::algorithm_iterator_copy<IteratorSourceFirst,
                                               IteratorSourceLast,
                                               IteratorDestinationFirst>())>
void copy(SourceMemoryBackendTag, IteratorSourceFirst source_first,
          IteratorSourceLast source_last, DestinationMemoryBackendTag,
          IteratorDestinationFirst destination_first) {
  copy(SourceMemoryBackendTag(), source_first, source_last,
       DestinationMemoryBackendTag(), destination_first, overload::selector());
}
}
}
