module;

#include <array>
#include <cmath>
#include <concepts>

export module colorspace:srgb;
import :rgb;
import :whitepoints;
import chromaticity;

namespace colorspace {

// Data from: https://en.wikipedia.org/wiki/SRGB
namespace srgb {

template < std::floating_point T >
inline T encode(T linear) noexcept {
	if (linear <= T(0.00313))
		return linear * T(12.9232102);
	return T(1.055) * std::pow(linear, T(1.0 / 2.4)) - T(0.055);
}

template < std::floating_point T >
inline T decode(T encoded) noexcept {
	if (encoded <= T(0.04045))
		return encoded / T(12.9232102);
	return std::pow((encoded + T(0.055)) / T(1.055), T(2.4));
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
inline constexpr XYY<T> GREEN{ T(0.3), T(0.6), T(1) };
export template < std::floating_point T >
inline constexpr XYY<T> BLUE{ T(0.15), T(0.06), T(1) };

export template < std::floating_point T >
inline constexpr std::array<T, 9> FROM_XYZ{ {
	T(3.2406), T(-1.5372), T(-0.4986),
	T(-0.9689), T(1.8758), T(0.0415),
	T(0.0557), T(-0.2040), T(1.057)
} };

export template < std::floating_point T >
inline constexpr std::array<T, 9> TO_XYZ{ {
	T(0.4124), T(0.3576), T(0.1805),
	T(0.2126), T(0.7152), T(0.0722),
	T(0.0193), T(0.1192), T(0.9505)
} };

} // namespace srgb

using namespace srgb;

export template < std::floating_point T >
inline constexpr RgbColorSpace<T> SRGB{ RED<T>, GREEN<T>, BLUE<T>, whitepoint::D65<T>, oetf<T>, eotf<T>, FROM_XYZ<T>, TO_XYZ<T> };

export template < std::floating_point T >
using SRgbLinear = RgbLinear<T, SRGB<T>>;
export template < std::floating_point T >
using SRgbEncoded = RgbEncoded<T, SRGB<T>>;

export using SRgbfLinear = SRgbLinear<float>;
export using SRgbdLinear = SRgbLinear<double>;

} // namespace colorspace 