#pragma once

#include <echo/memory/simd_allocator.h>

namespace echo {
namespace memory {

////////////////////////
// StaticMemoryBuffer //
////////////////////////

template <class T, int NumElements, int Alignment>
class StaticMemoryBuffer {
  static_assert(NumElements != NumElements,
                "Buffer with given alignment is not supported");
};

template <class T, int NumElements>
class StaticMemoryBuffer<T, NumElements, 0> {
 public:
  T* data() { return _data; }
  const T* data() const { return _data; }
  const T* const_data() const { return _data; }

 private:
  T _data[NumElements];
};

#define MAKE_STATIC_MEMORY_BUFFER(ALIGNMENT)                               \
  template <class T, int NumElements>                                      \
  class alignas(ALIGNMENT) StaticMemoryBuffer<T, NumElements, ALIGNMENT> { \
   public:                                                                 \
    T* data() { return _data; }                                            \
    const T* data() const { return _data; }                                \
    const T* const_data() const { return _data; }                          \
                                                                           \
   private:                                                                \
    T _data[NumElements];                                                  \
  };

MAKE_STATIC_MEMORY_BUFFER(1)
MAKE_STATIC_MEMORY_BUFFER(32)
MAKE_STATIC_MEMORY_BUFFER(64)
MAKE_STATIC_MEMORY_BUFFER(128)

#undef MAKE_STATIC_MEMORY_BUFFER

/////////////////////
// StaticAllocator //
/////////////////////

template <class T, int Alignment = 0>
struct StaticAllocator {
  using value_type = T;
  template <int NumElements>
  using buffer_type = StaticMemoryBuffer<T, NumElements, Alignment>;
};

template <class T>
using SimdStaticAllocator = StaticAllocator<T, ECHO_SIMD_ALIGNMENT>;

}  // end namespcae memory
}  // end namespace echo
