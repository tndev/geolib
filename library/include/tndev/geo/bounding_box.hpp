#pragma once

namespace tndev::geo {
template <typename T>
struct bounding_box {

    bounding_box() = default;
    ~bounding_box() = default;
    bounding_box(const bounding_box&) = default;
    bounding_box(bounding_box&& bounding_box) noexcept = default;

    constexpr auto operator=(const bounding_box& p) -> bounding_box& = default;
    constexpr auto operator=(bounding_box&& p) noexcept
        -> bounding_box& = default;

    bounding_box(const T& topleft, const T& bottomright)
        : m_topleft(topleft), m_bottomright(bottomright) {}

    auto topleft() const -> T { return m_topleft; }
    auto bottomright() const -> T { return m_bottomright; }

  private:
    T m_topleft;
    T m_bottomright;
};
} // namespace tndev::geo