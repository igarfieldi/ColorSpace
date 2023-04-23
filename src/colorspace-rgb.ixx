module;

#include <array>
#include <cassert>
#include <cmath>
#include <concepts>
#include <string>

export module colorspace:rgb;

import chromaticity;
import colorspace.xyz;

namespace colorspace {

export template < std::floating_point T >
using TransferFunction = std::array<T, 3>(*)(const std::array<T, 3>&) noexcept;

export template < std::floating_point T >
struct RgbColorSpace {
	using Type = T;

	// Primaries
	XYY<T> red;
	XYY<T> green;
	XYY<T> blue;

	XYY<T> white;

	TransferFunction<T> oetf;
	TransferFunction<T> eotf;

	std::array<T, 9> from_xyz;
	std::array<T, 9> to_xyz;
};

template < std::floating_point T >
class RgbData {
public:
	constexpr RgbData(std::array<T, 3> values) : _values{values} {}

	constexpr T& r() noexcept { return _values[0]; }
	constexpr T& g() noexcept { return _values[1]; }
	constexpr T& b() noexcept { return _values[2]; }
	constexpr const T& r() const noexcept { return _values[0]; }
	constexpr const T& g() const noexcept { return _values[1]; }
	constexpr const T& b() const noexcept { return _values[2]; }

	T& operator[](size_t index) noexcept {
		assert(index < 3);
		return _values[index];
	}
	const T& operator[](size_t index) const noexcept {
		assert(index < 3);
		return _values[index];
	}

	constexpr std::array<T, 3>& raw() noexcept {
		return _values;
	}
	constexpr const std::array<T, 3>& raw() const noexcept {
		return _values;
	}

	constexpr std::array<T, 3>::iterator begin() noexcept {
		return _values.begin();
	}
	constexpr std::array<T, 3>::const_iterator begin() const noexcept {
		return _values.begin();
	}
	constexpr std::array<T, 3>::const_iterator cbegin() const noexcept {
		return _values.cbegin();
	}
	constexpr std::array<T, 3>::reverse_iterator rbegin() noexcept {
		return _values.rbegin();
	}
	constexpr std::array<T, 3>::const_reverse_iterator rbegin() const noexcept {
		return _values.rbegin();
	}
	constexpr std::array<T, 3>::const_reverse_iterator crbegin() const noexcept {
		return _values.crbegin();
	}

	constexpr std::array<T, 3>::iterator end() noexcept {
		return _values.begin();
	}
	constexpr std::array<T, 3>::const_iterator end() const noexcept {
		return _values.begin();
	}
	constexpr std::array<T, 3>::const_iterator cend() const noexcept {
		return _values.cbegin();
	}
	constexpr std::array<T, 3>::reverse_iterator rend() noexcept {
		return _values.rbegin();
	}
	constexpr std::array<T, 3>::const_reverse_iterator rend() const noexcept {
		return _values.rbegin();
	}
	constexpr std::array<T, 3>::const_reverse_iterator crend() const noexcept {
		return _values.crbegin();
	}

protected:
	std::array<T, 3> _values;
};

template < template < std::floating_point T, RgbColorSpace<T>, bool > class RGB, std::floating_point T, RgbColorSpace<T> C, bool LINEAR >
struct RgbBase;

template < template < std::floating_point T, RgbColorSpace<T>, bool > class RGB, std::floating_point T, RgbColorSpace<T> C >
struct RgbBase<RGB, T, C, true> : public RgbData<T> {
	using RgbData<T>::RgbData;

	RGB<T, C, false> encode() const noexcept {
		return RGB<T, C, false>(C.oetf(this->_values));
	}
};

template < template < std::floating_point T, RgbColorSpace<T>, bool > class RGB, std::floating_point T, RgbColorSpace<T> C >
struct RgbBase<RGB, T, C, false> : public RgbData<T> {
	using RgbData<T>::RgbData;

	RGB<T, C, true> decode() const noexcept {
		return RGB<T, C, true>(C.eotf(this->_values));
	}
};

export template < std::floating_point T, RgbColorSpace<T> C, bool L >
class Rgb : public RgbBase<Rgb, T, C, L> {
public:
	using Type = T;
	static constexpr RgbColorSpace<T> COLOR_SPACE = C;
	static constexpr bool IS_LINEAR = L;

	constexpr Rgb() : Rgb(T(0)) {}
	constexpr explicit Rgb(T val) : Rgb(val, val, val) {}
	constexpr Rgb(T r, T g, T b) : Rgb{ std::array<T, 3>{ { r, g, b }} } {}
	constexpr Rgb(std::array<T, 3> rgb) : RgbBase<Rgb, T, C, L>{ rgb } {}

	template < XYY<T> W = C.white >
	explicit Rgb(const XYZ<T, W>& xyz) :
		Rgb((adaptation_cat_02<T, W, C.white>()* xyz).raw())
	{}

	template < RgbColorSpace<T> C2 >
	explicit Rgb(const Rgb<T, C2, L>& rgb) :
		Rgb((math::Mat3<T>(C.from_xyz)* adaptation_cat_02<T, C2.white, C.white>()* math::Mat3<T>(C.to_xyz)* XYZ<T, C.white>(rgb.r(), rgb.g(), rgb.b())).raw())
	{}

	constexpr Rgb& operator+=(const Rgb& rhs) noexcept {
		for (size_t i = 0u; i < this->_values.size(); ++i)
			this->_values[i] += rhs._values[i];
		return *this;
	}
	constexpr Rgb& operator-=(const Rgb& rhs) noexcept {
		for (size_t i = 0u; i < this->_values.size(); ++i)
			this->_values[i] -= rhs._values[i];
		return *this;
	}
	constexpr Rgb& operator*=(const Rgb& rhs) noexcept {
		for (size_t i = 0u; i < this->_values.size(); ++i)
			this->_values[i] *= rhs._values[i];
		return *this;
	}
	constexpr Rgb& operator/=(const Rgb& rhs) noexcept {
		for (size_t i = 0u; i < this->_values.size(); ++i)
			this->_values[i] /= rhs._values[i];
		return *this;
	}

	constexpr Rgb& operator+=(T rhs) noexcept {
		for (size_t i = 0u; i < this->_values.size(); ++i)
			this->_values[i] += rhs;
		return *this;
	}
	constexpr Rgb& operator-=(T rhs) noexcept {
		for (size_t i = 0u; i < this->_values.size(); ++i)
			this->_values[i] -= rhs;
		return *this;
	}
	constexpr Rgb& operator*=(T rhs) noexcept {
		for (size_t i = 0u; i < this->_values.size(); ++i)
			this->_values[i] *= rhs;
		return *this;
	}
	constexpr Rgb& operator/=(T rhs) noexcept {
		for (size_t i = 0u; i < this->_values.size(); ++i)
			this->_values[i] /= rhs;
		return *this;
	}

	constexpr Rgb operator-() const noexcept {
		return Rgb(-this->r(), -this->g(), -this->b());
	}

	Rgb abs() const noexcept {
		return Rgb(std::abs(this->r()), std::abs(this->g()), std::abs(this->b()));
	}
	Rgb sqrt() const noexcept {
		return Rgb(std::sqrt(this->r()), std::sqrt(this->g()), std::sqrt(this->b()));
	}
	Rgb pow(T exp) const noexcept {
		return Rgb(std::pow(this->r(), exp), std::pow(this->g(), exp), std::pow(this->b(), exp));
	}
	Rgb exp() const noexcept {
		return Rgb(std::exp(this->r()), std::exp(this->g()), std::exp(this->b()));
	}

	constexpr Rgb normalize() const noexcept {
		const auto max_elem = std::max(this->r(), std::max(this->g(), this->b()));
		return Rgb(this->r() / max_elem, this->g() / max_elem, this->b() / max_elem);
	}

	template < XYY<T> C2 >
	operator XYZ<T, C2>() const noexcept {
		const math::Mat3<T> to_xyz(C.to_xyz);
		const auto cat02 = adaptation_cat_02<T, C2, C.white>();
		const XYZ<T, C2> xyz(this->r(), this->g(), this->b());
		return (to_xyz * cat02) * xyz;
	}
};

export template < class T, RgbColorSpace<T> C >
using RgbLinear = Rgb<T, C, true>;
export template < class T, RgbColorSpace<T> C >
using RgbEncoded = Rgb<T, C, false>;

export template < RgbColorSpace<float> C >
using RgbfLinear = Rgb<float, C, true>;
export template < RgbColorSpace<double> C >
using RgbdLinear = Rgb<double, C, true>;
export template < RgbColorSpace<float> C >
using RgbfEncoded = Rgb<float, C, false>;
export template < RgbColorSpace<double> C >
using RgbdEncoded = Rgb<double, C, false>;

export template < class T, RgbColorSpace<T> C, bool L >
std::string to_string(const Rgb<T, C, L>& rgb) {
	return std::string("[") + std::to_string(rgb.r()) + "," + std::to_string(rgb.g()) + "," + std::to_string(rgb.b()) + "]";
}

} // namespace colorspace
