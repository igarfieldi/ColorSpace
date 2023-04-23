module;

#include <array>
#include <cmath>
#include <concepts>

export module colorspace:adobe;
import :rgb;
import :whitepoints;
import chromaticity;

namespace colorspace {

// Data from: https://en.wikipedia.org/wiki/Adobe_RGB_color_space
namespace adobe_rgb_1998 {

template < std::floating_point T >
inline T encode(T linear) noexcept {
	return std::pow(linear, T(1.0 / 2.19921875));
}

template < std::floating_point T >
inline T decode(T encoded) noexcept {
	return std::pow(encoded, T(2.19921875));
}

export template < std::floating_point T >
std::array<T, 3> oetf(const std::array<T, 3>& linear) noexcept {
	return std::array<T, 3>{ { encode(linear[0]), encode(linear[1]), encode(linear[2]) }};
}

export template < std::floating_point T >
std::array<T, 3> eotf(const std::array<T, 3>& encoded) noexcept {
	return std::array<T, 3>{ { decode(encoded[0]), decode(encoded[1]), decode(encoded[2]) }};
}

export template < std::floating_point T >
inline constexpr XYY<T> RED{ T(0.64), T(0.33), T(1) };
export template < std::floating_point T >
inline constexpr XYY<T> GREEN{ T(0.21), T(0.71), T(1) };
export template < std::floating_point T >
inline constexpr XYY<T> BLUE{ T(0.15), T(0.06), T(1) };

export template < std::floating_point T >
inline constexpr std::array<T, 9> FROM_XYZ{ {
	T(2.04159), T(-0.56501), T(-0.34473),
	T(-0.96924), T(1.87597), T(0.04156),
	T(0.01344), T(-0.11836), T(1.01517)
} };

export template < std::floating_point T >
inline constexpr std::array<T, 9> TO_XYZ{ {
	T(0.57667), T(0.18556), T(0.18823),
	T(0.29734), T(0.62736), T(0.07529),
	T(0.02703), T(0.07069), T(0.99134)
} };

} // namespace adobe_rgb_1998

using namespace adobe_rgb_1998;

export template < std::floating_point T >
inline constexpr RgbColorSpace<T> ADOBE_RGB_1998{ RED<T>, GREEN<T>, BLUE<T>, whitepoint::D65<T>, oetf<T>, eotf<T>, FROM_XYZ<T>, TO_XYZ<T> };

} // namespace colorspace 