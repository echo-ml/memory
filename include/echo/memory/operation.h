#pragma once

#include <cstring>

#include <echo/memory/standard_memory_backend_tag.h>

namespace echo {
namespace memory {

inline void* memcpy(standard_memory_backend_tag, void* destination, void* source,
                    std::size_t num) {
  return std::memcpy(destination, source, num);
}

template<class Tag>
void* memcpy(Tag, void* destination, Tag, void* source, std::size_t num) {
  return memcpy(Tag(), destination, source, num);
}

inline void* memset(standard_memory_backend_tag, void* ptr, int value,
                    std::size_t num) {
  return std::memset(ptr, value, num);
}

inline int memcmp(standard_memory_backend_tag, void* ptr1, void* ptr2,
                  std::size_t num) {
  return std::memcmp(ptr1, ptr2, num);
}

} // end namespace memory
} // end namespace echo
