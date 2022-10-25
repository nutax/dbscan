#ifndef __SIMD_H__
#define __SIMD_H__

#include <eve/algo/container/soa_vector.hpp>
#include <eve/algo/transform.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <stdint.h>
#include "core/measure.h"

#define STRUCT(_struct_name, ...) struct _struct_name : eve::struct_support<_struct_name, __VA_ARGS__>
#define STRUCT_NO_COMPARATORS using eve_disable_ordering = void
#define STRUCT_DATA(_data_number, _struct_name, _data_name)                   \
    friend decltype(auto) get##_data_name(eve::like<_struct_name> auto &&self) \
    {                                                                          \
        return get<_data_number>(std::forward<decltype(self)>(self));          \
    }

namespace simd = eve;

#endif