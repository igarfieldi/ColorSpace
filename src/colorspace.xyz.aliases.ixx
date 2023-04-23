module;

#include <concepts>

export module colorspace.xyz.aliases;
import colorspace;
import colorspace.xyz;

export namespace colorspace {

export template < std::floating_point T >
using XYZ_D50 = XYZ<T, whitepoint::D50<T>>;
export template < std::floating_point T >
using XYZ_D55 = XYZ<T, whitepoint::D55<T>>;
export template < std::floating_point T >
using XYZ_D60 = XYZ<T, whitepoint::D60<T>>;
export template < std::floating_point T >
using XYZ_D65 = XYZ<T, whitepoint::D65<T>>;
export template < std::floating_point T >
using XYZ_DCI = XYZ<T, whitepoint::DCI<T>>;
export template < std::floating_point T >
using XYZ_ACES = XYZ<T, whitepoint::ACES<T>>;

export using XYZf_D50 = XYZ<float, whitepoint::D50<float>>;
export using XYZf_D55 = XYZ<float, whitepoint::D55<float>>;
export using XYZf_D60 = XYZ<float, whitepoint::D60<float>>;
export using XYZf_D65 = XYZ<float, whitepoint::D65<float>>;
export using XYZf_DCI = XYZ<float, whitepoint::DCI<float>>;
export using XYZf_ACES = XYZ<float, whitepoint::ACES<float>>;
export using XYZd_D50 = XYZ<double, whitepoint::D50<double>>;
export using XYZd_D55 = XYZ<double, whitepoint::D55<double>>;
export using XYZd_D60 = XYZ<double, whitepoint::D60<double>>;
export using XYZd_D65 = XYZ<double, whitepoint::D65<double>>;
export using XYZd_DCI = XYZ<double, whitepoint::DCI<double>>;
export using XYZd_ACES = XYZ<double, whitepoint::ACES<double>>;

} // namespace colorspace