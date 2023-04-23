module;

#include <array>
#include <cmath>
#include <concepts>

export module colorspace:dcip3;
import :rgb;
import :whitepoints;
import chromaticity;

namespace colorspace {

// Data from: https://en.wikipedia.org/wiki/DCI-P3
namespace dci_p3 {

template < std::floating_point T >
inline T encode(T linear) noexcept {
	return std::pow(linear, T(1.0 / 2.6));
}

template < std::floating_point T >
inline T decode(T encoded) noexcept {
	return std::pow(encoded, T(2.6));
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
inline constexpr XYY<T> RED{ T(0.68), T(0.32), T(1) };
export template < std::floating_point T >
inline constexpr XYY<T> GREEN{ T(0.265), T(0.69), T(1) };
export template < std::floating_point T >
inline constexpr XYY<T> BLUE{ T(0.15), T(0.06), T(1) };

export template < std::floating_point T >
inline constexpr std::array<T, 9> FROM_XYZ{ {
	T(2.725394), T(-1.018003), T(-0.4401632),
	T(-0.795168), T(1.6897321), T(0.0226472),
	T(0.0412419), T(-0.087639), T(1.1009294)
} };

export template < std::floating_point T >
inline constexpr std::array<T, 9> TO_XYZ{ {
	T(0.4451698), T(0.2771344), T(0.1722827),
	T(0.2094917), T(0.7215953), T(0.0689131),
	T(0.0), T(0.0470606), T(0.9073554)
} };

} // namespace dci_p3

using namespace dci_p3;

export template < std::floating_point T >
inline constexpr RgbColorSpace<T> DCI_P3{ RED<T>, GREEN<T>, BLUE<T>, whitepoint::DCI<T>, oetf<T>, eotf<T>, FROM_XYZ<T>, TO_XYZ<T> };
export template < std::floating_point T >
inline constexpr RgbColorSpace<T> DCI_P3_D65{ RED<T>, GREEN<T>, BLUE<T>, whitepoint::D65<T>, oetf<T>, eotf<T>, FROM_XYZ<T>, TO_XYZ<T> };

} // namespace colorspace 