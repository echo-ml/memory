#pragma once

#include <cstring>

#include <echo/memory/memory_backend_tag.h>
#include <echo/memory/concept.h>

namespace echo {
namespace memory {

inline void* memcpy(memory_backend_tag, void* destination, const void* source,
                    std::size_t num) {
  return std::memcpy(destination, source, num);
}

inline void* memcpy(memory_backend_tag, void* destination, memory_backend_tag,
                    const void* source, std::size_t num) {
  return memcpy(memory_backend_tag(), destination, source, num);
}

template <class MemoryBackendTag,
          CONCEPT_REQUIRES(concept::memory_backend_tag<MemoryBackendTag>())>
void* memcpy(MemoryBackendTag, void* destination, MemoryBackendTag,
             const void* source, std::size_t num) {
  return memcpy(MemoryBackendTag(), destination, source, num);
}

inline void* memset(memory_backend_tag, void* ptr, int value, std::size_t num) {
  return std::memset(ptr, value, num);
}

inline int memcmp(memory_backend_tag, void* ptr1, void* ptr2, std::size_t num) {
  return std::memcmp(ptr1, ptr2, num);
}

}  // end namespace memory
}  // end namespace echo
