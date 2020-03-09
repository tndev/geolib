#pragma once

#include <tndev/geo/extent.hpp>

#include <cmath>
#include <ratio>

namespace tndev::geo {

template <class Rep, class Period>
using length [[deprecated]] = extent<Rep, Period>;

template <class ToExtent, class Rep, class Period>
[[deprecated]] constexpr auto length_cast(const extent<Rep, Period>& d)
    -> ToExtent {
    return extent_cast<ToExtent, Rep, Period>(d);
}

} // namespace tndev::geo