module;

#include <concepts>

export module chromaticity;

namespace colorspace {

export template < std::floating_point T >
struct XYY {
	using Type = T;

	T x;
	T y;
	T Y;
};

export template < std::floating_point T >
constexpr bool operator==(const XYY<T>& lhs, const XYY<T>& rhs) noexcept {
	return lhs.x == rhs.x && lhs.y == rhs.y && lhs.Y == rhs.Y;
}

} // namespace colorspace