#pragma once

#include <boost/align/aligned_allocator.hpp>

#ifndef ECHO_SIMD_ALIGNMENT
#define ECHO_SIMD_ALIGNMENT 64
#endif

namespace echo {
namespace memory {
//------------------------------------------------------------------------------
// SimdAllocator
//------------------------------------------------------------------------------
template <class T>
using SimdAllocator =
    boost::alignment::aligned_allocator<T, ECHO_SIMD_ALIGNMENT>;

}  // end namespace memory
}  // end namespace echo
