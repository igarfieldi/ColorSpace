module;

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <concepts>
#include <tuple>

export module spectrum:spd;
import :cie;
import :iterator;
import :shape;
import spectrum.blackbody;
import colorspace.xyz;
import chromaticity;

namespace spectral {

export template < std::floating_point T, size_t N, SpdShape<T, N> S >
class Spd {
public:
	using Type = T;
	static constexpr size_t WAVELENGTH_COUNT = N;
	static constexpr size_t SAMPLE_COUNT = WAVELENGTH_COUNT - 1;
	static constexpr SpdShape<T, N> SHAPE = S;
	static constexpr bool IS_UNIFORM = SHAPE.is_uniform();

	using iterator = SpdIterator<T, WAVELENGTH_COUNT, S, false>;
	using const_iterator = SpdIterator<T, WAVELENGTH_COUNT, S, true>;
	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;

	static_assert(SHAPE.is_sorted(), "The SPD shape (aka. its wavelengths must be sorted in ascending order");
	static_assert(N >= 2, "Need at least two wavelengths to create an interval");

	constexpr Spd(T val = T(0)) noexcept {
		std::fill(_coefficients.begin(), _coefficients.end(), val);
	}

	constexpr Spd(const std::array<T, SAMPLE_COUNT>& coefficients) noexcept : _coefficients(coefficients) {}

	static Spd blackbody(T temperature_kelvin) noexcept {
		std::array<T, SAMPLE_COUNT> coeffs;
		for (size_t i = 0u; i < SAMPLE_COUNT; ++i)
			coeffs[i] = blackbody::compute_radiance(S.wavelengths_nm[i] + T(0.5) * (S.wavelengths_nm[i + 1] - S.wavelengths_nm[i]), temperature_kelvin);
		return Spd(coeffs);
	}

	constexpr T& operator[](size_t index) noexcept {
		assert(index < SAMPLE_COUNT);
		return _coefficients[index];
	}
	constexpr const T& operator[](size_t index) const noexcept {
		assert(index < SAMPLE_COUNT);
		return _coefficients[index];
	}

	iterator begin() noexcept {
		return iterator::begin(_coefficients);
	}
	const_iterator begin() const noexcept {
		return const_iterator::begin(_coefficients);
	}
	const_iterator cbegin() const noexcept {
		return const_iterator::begin(_coefficients);
	}
	reverse_iterator rbegin() noexcept {
		return reverse_iterator(iterator::end(_coefficients));
	}
	const_reverse_iterator rbegin() const noexcept {
		return const_reverse_iterator(const_iterator::end(_coefficients));
	}
	const_reverse_iterator crbegin() const noexcept {
		return const_reverse_iterator(const_iterator::end(_coefficients));
	}

	iterator end() noexcept {
		return iterator::end(_coefficients);
	}
	const_iterator end() const noexcept {
		return const_iterator::end(_coefficients);
	}
	const_iterator cend() const noexcept {
		return const_iterator::end(_coefficients);
	}
	reverse_iterator rend() noexcept {
		return reverse_iterator(iterator::begin(_coefficients));
	}
	const_reverse_iterator rend() const noexcept {
		return const_reverse_iterator(const_iterator::begin(_coefficients));
	}
	const_reverse_iterator crend() const noexcept {
		return const_reverse_iterator(const_iterator::begin(_coefficients));
	}

	constexpr Spd& operator+=(const Spd& rhs) noexcept {
		for (size_t i = 0u; i < _coefficients.size(); ++i)
			_coefficients[i] += rhs._coefficients[i];
		return *this;
	}
	constexpr Spd& operator-=(const Spd& rhs) noexcept {
		for (size_t i = 0u; i < _coefficients.size(); ++i)
			_coefficients[i] -= rhs._coefficients[i];
		return *this;
	}
	constexpr Spd& operator*=(const Spd& rhs) noexcept {
		for (size_t i = 0u; i < _coefficients.size(); ++i)
			_coefficients[i] *= rhs._coefficients[i];
		return *this;
	}
	constexpr Spd& operator/=(const Spd& rhs) noexcept {
		for (size_t i = 0u; i < _coefficients.size(); ++i)
			_coefficients[i] /= rhs._coefficients[i];
		return *this;
	}

	constexpr Spd& operator+=(T rhs) noexcept {
		for (T& coef : _coefficients)
			coef += rhs;
		return *this;
	}
	constexpr Spd& operator-=(T rhs) noexcept {
		for (T& coef : _coefficients)
			coef -= rhs;
		return *this;
	}
	constexpr Spd& operator*=(T rhs) noexcept {
		for (T& coef : _coefficients)
			coef *= rhs;
		return *this;
	}
	constexpr Spd& operator/=(T rhs) noexcept {
		for (T& coef : _coefficients)
			coef /= rhs;
		return *this;
	}

	constexpr std::array<T, SAMPLE_COUNT>& coefficients() noexcept {
		return _coefficients;
	}
	constexpr const std::array<T, SAMPLE_COUNT>& coefficients() const noexcept {
		return _coefficients;
	}

	constexpr bool is_black() const noexcept {
		for (const T& coef : _coefficients)
			if (coef != T(0))
				return false;
		return true;
	}

	Spd sqrt() const noexcept {
		std::array<T, SAMPLE_COUNT> coefs;
		for (size_t i = 0u; i < _coefficients.size(); ++i)
			coefs[i] = std::sqrt(_coefficients[i]);
		return Spd(coefs);
	}
	Spd pow(T expo) const noexcept {
		std::array<T, SAMPLE_COUNT> coefs;
		for (size_t i = 0u; i < _coefficients.size(); ++i)
			coefs[i] = std::pow(_coefficients[i], expo);
		return Spd(coefs);
	}
	Spd exp() const noexcept {
		std::array<T, SAMPLE_COUNT> coefs;
		for (size_t i = 0u; i < _coefficients.size(); ++i)
			coefs[i] = std::exp(_coefficients[i]);
		return Spd(coefs);
	}
	constexpr Spd clamp(T min, T max) const noexcept {
		std::array<T, SAMPLE_COUNT> coefs;
		for (size_t i = 0u; i < _coefficients.size(); ++i)
			coefs[i] = std::clamp(_coefficients[i], min, max);
		return Spd(coefs);
	}

	SpdSample<T> min() const noexcept {
		const auto iter = std::min_element(_coefficients.cbegin(), _coefficients.cend());
		return SpdSample<T>{*iter, S.wavelengths_nm[iter - _coefficients.cbegin()]};
	}
	SpdSample<T> max() const noexcept {
		const auto iter = std::max_element(_coefficients.cbegin(), _coefficients.cend());
		return SpdSample<T>{*iter, S.wavelengths_nm[iter - _coefficients.cbegin()]};
	}

	const Spd min(const Spd& other) const noexcept {
		std::array<T, SAMPLE_COUNT> coefs;
		for (size_t i = 0u; i < _coefficients.size(); ++i)
			coefs[i] = std::min(_coefficients[i], other._coefficients[i]);
		return Spd(coefs);
	}
	const T max(const Spd& other) const noexcept {
		std::array<T, SAMPLE_COUNT> coefs;
		for (size_t i = 0u; i < _coefficients.size(); ++i)
			coefs[i] = std::max(_coefficients[i], other._coefficients[i]);
		return Spd(coefs);
	}
	
	template < colorspace::XYY<T> W >
	explicit constexpr operator colorspace::XYZ<T, W>() const noexcept {
		constexpr auto MATCHING_FUNCTIONS = cie::compute_matching_functions(SHAPE);
		std::array<T, 3> xyz{ {T(0), T(0), T(0)} };
		for (size_t i = 0u; i < SAMPLE_COUNT; ++i)
			for (size_t j = 0u; j < 3u; ++j)
				xyz[j] += _coefficients[i] * MATCHING_FUNCTIONS[j][i];

		const auto scale = (SHAPE.wavelengths_nm.back() - SHAPE.wavelengths_nm.front()) / (cie::Y_INTEGRAL<T> * static_cast<T>(SAMPLE_COUNT));
		for (size_t i = 0u; i < 3u; ++i)
			xyz[i] *= scale;

		return colorspace::XYZ<T, W>(xyz);
	}

	constexpr auto operator<=>(const Spd& rhs) const noexcept {
		for (size_t i = 0u; i + 1 < _coefficients.size(); ++i)
			if (const auto cmp = _coefficients[i] <=> rhs._coefficients[i]; cmp != 0)
				return cmp;
		return _coefficients.back() <=> rhs._coefficients.back();
	}
	
private:
	std::array<T, SAMPLE_COUNT> _coefficients;
};

// ##############################################################################

export template < std::floating_point T, size_t N, SpdShape<T, N> S >
constexpr Spd<T, N, S> operator+(Spd<T, N, S> lhs, const Spd<T, N, S>& rhs) noexcept {
	return lhs += rhs;
}
export template < std::floating_point T, size_t N, SpdShape<T, N> S >
constexpr Spd<T, N, S> operator-(Spd<T, N, S> lhs, const Spd<T, N, S>& rhs) noexcept {
	return lhs -= rhs;
}
export template < std::floating_point T, size_t N, SpdShape<T, N> S >
constexpr Spd<T, N, S> operator*(Spd<T, N, S> lhs, const Spd<T, N, S>& rhs) noexcept {
	return lhs *= rhs;
}
export template < std::floating_point T, size_t N, SpdShape<T, N> S >
constexpr Spd<T, N, S> operator/(Spd<T, N, S> lhs, const Spd<T, N, S>& rhs) noexcept {
	return lhs /= rhs;
}

export template < std::floating_point T, size_t N, SpdShape<T, N> S >
constexpr Spd<T, N, S> operator+(Spd<T, N, S> lhs, T rhs) noexcept {
	return lhs += rhs;
}
export template < std::floating_point T, size_t N, SpdShape<T, N> S >
constexpr Spd<T, N, S> operator-(Spd<T, N, S> lhs, T rhs) noexcept {
	return lhs -= rhs;
}
export template < std::floating_point T, size_t N, SpdShape<T, N> S >
constexpr Spd<T, N, S> operator*(Spd<T, N, S> lhs, T rhs) noexcept {
	return lhs *= rhs;
}
export template < std::floating_point T, size_t N, SpdShape<T, N> S >
constexpr Spd<T, N, S> operator/(Spd<T, N, S> lhs, T rhs) noexcept {
	return lhs /= rhs;
}

export template < std::floating_point T, size_t N, SpdShape<T, N> S >
constexpr Spd<T, N, S> operator+(T lhs, Spd<T, N, S> rhs) noexcept {
	return rhs += lhs;
}
export template < std::floating_point T, size_t N, SpdShape<T, N> S >
constexpr Spd<T, N, S> operator*(T lhs, Spd<T, N, S> rhs) noexcept {
	return rhs *= lhs;
}

} // namespace spectral