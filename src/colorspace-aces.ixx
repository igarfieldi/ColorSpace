module;

#include <array>
#include <cmath>
#include <concepts>

export module colorspace:aces;
import :rgb;
import :whitepoints;
import chromaticity;

namespace colorspace {

// Data from: https://en.wikipedia.org/wiki/Academy_Color_Encoding_System
namespace aces {

export template < std::floating_point T >
std::array<T, 3> oetf(const std::array<T, 3>& linear) noexcept {
	return linear;
}

export template < std::floating_point T >
std::array<T, 3> eotf(const std::array<T, 3>& encoded) noexcept {
	return encoded;
}

export template < std::floating_point T >
inline constexpr XYY<T> RED{ T(0.7347), T(0.2653), T(1) };
export template < std::floating_point T >
inline constexpr XYY<T> GREEN{ T(0.0), T(1.0), T(1) };
export template < std::floating_point T >
inline constexpr XYY<T> BLUE{ T(0.0001), T(-0.077), T(1) };

export template < std::floating_point T >
inline constexpr std::array<T, 9> FROM_XYZ{ {
	T(1.0498110175), T(0.0), T(-0.0000974845),
	T(-0.4959030231), T(1.3733130458), T(0.0982400361),
	T(0.0), T(0.0), T(0.9912520182)
} };

export template < std::floating_point T >
inline constexpr std::array<T, 9> TO_XYZ{ {
	T(0.9525523959), T(0.0), T(0.0000936786),
	T(0.3439664498), T(0.7281660966), T(-0.0721325464),
	T(0.0), T(0.0), T(1.0088251844)
} };

} // namespace aces

using namespace aces;

export template < std::floating_point T >
inline constexpr RgbColorSpace<T> ACES{ RED<T>, GREEN<T>, BLUE<T>, whitepoint::ACES<T>, oetf<T>, eotf<T>, FROM_XYZ<T>, TO_XYZ<T> };

} // namespace colorspace 