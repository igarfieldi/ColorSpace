module;

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <concepts>

export module spectrum:coefficient;

export namespace spectral {

template < std::floating_point T, size_t N >
class CoefficientSpectrum {
public:
	static constexpr size_t SAMPLES = N;
	using Type = T;

	CoefficientSpectrum(Type value) {
		std::fill(std::begin(_coefficients), std::end(_coefficients), value);
	}
	CoefficientSpectrum(const std::array<Type, SAMPLES>& coefs) : _coefficients{ coefs } {}

	CoefficientSpectrum(const CoefficientSpectrum&) noexcept = default;
	CoefficientSpectrum(CoefficientSpectrum&&) noexcept = default;
	CoefficientSpectrum& operator=(const CoefficientSpectrum&) noexcept = default;
	CoefficientSpectrum& operator=(CoefficientSpectrum&&) noexcept = default;
	~CoefficientSpectrum() noexcept = default;

	T& operator[](size_t index) noexcept {
		assert(index < SAMPLES);
		return _coefficients[index];
	}
	const T& operator[](size_t index) const noexcept {
		assert(index < SAMPLES);
		return _coefficients[index];
	}
	T& at(size_t index) {
		return _coefficients.at(index);
	}
	const T& at(size_t index) const {
		return _coefficients.at(index);
	}

	CoefficientSpectrum& operator+=(const CoefficientSpectrum& rhs) noexcept {
		for (size_t i = 0u; i < SAMPLES; ++i)
			_coefficients[i] += rhs._coefficients[i];
	}
	CoefficientSpectrum& operator-=(const CoefficientSpectrum& rhs) noexcept {
		for (size_t i = 0u; i < SAMPLES; ++i)
			_coefficients[i] -= rhs._coefficients[i];
	}
	CoefficientSpectrum& operator*=(const CoefficientSpectrum& rhs) noexcept {
		for (size_t i = 0u; i < SAMPLES; ++i)
			_coefficients[i] *= rhs._coefficients[i];
	}
	CoefficientSpectrum& operator/=(const CoefficientSpectrum& rhs) noexcept {
		for (size_t i = 0u; i < SAMPLES; ++i)
			_coefficients[i] /= rhs._coefficients[i];
	}

	CoefficientSpectrum& operator*=(T value) noexcept {
		for (size_t i = 0u; i < SAMPLES; ++i)
			_coefficients[i] *= value;
	}
	CoefficientSpectrum& operator/=(T value) noexcept {
		for (size_t i = 0u; i < SAMPLES; ++i)
			_coefficients[i] /= value;
	}

	CoefficientSpectrum operator-() const noexcept {
		std::array<Type, SAMPLES> coeffs;
		for (size_t i = 0u; i < SAMPLES; ++i)
			coeffs[i] = -_coefficients[i];
		return CoefficientSpectrum(coeffs);
	}

	bool operator==(const CoefficientSpectrum& other) const noexcept {
		for (size_t i = 0u; i < SAMPLES; ++i)
			if (_coefficients[i] != other._coefficients[i])
				return false;
		return true;
	}
	bool operator!=(const CoefficientSpectrum& other) const noexcept {
		for (size_t i = 0u; i < SAMPLES; ++i)
			if (_coefficients[i] == other._coefficients[i])
				return false;
		return true;
	}
	bool operator<(const CoefficientSpectrum& other) const noexcept {
		for (size_t i = 0u; i < SAMPLES; ++i)
			if (_coefficients[i] >= other._coefficients[i])
				return false;
		return true;
	}

	CoefficientSpectrum& sqrt() noexcept {
		for (T& value : _coefficients)
			value = std::sqrt(value);
	}
	CoefficientSpectrum& pow(T exp) noexcept {
		for (T& value : _coefficients)
			value = std::pow(value, exp);
	}
	CoefficientSpectrum& exp() noexcept {
		for (T& value : _coefficients)
			value = std::exp(value);
	}
	CoefficientSpectrum& clamp(T min, T max) noexcept {
		for (T& value : _coefficients)
			value = std::clamp(value, min, max);
	}

	bool is_black() const noexcept {
		for (T coef : _coefficients)
			if (coef != T(0))
				return false;
		return true;
	}
	T min() const noexcept {
		T min_value = _coefficients[0];
		for (size_t i = 1u; i < SAMPLES; ++i)
			min_value = std::min(min_value, _coefficients[i]);
		return min_value;
	}
	T max() const noexcept {
		T max_value = _coefficients[0];
		for (size_t i = 1u; i < SAMPLES; ++i)
			max_value = std::max(max_value, _coefficients[i]);
		return max_value;
	}
	CoefficientSpectrum min(const CoefficientSpectrum& rhs) const noexcept {
		std::array<Type, SAMPLES> coeffs;
		for (size_t i = 0u; i < SAMPLES; ++i)
			coeffs[i] = std::min(_coefficients[i], rhs._coefficients[i]);
		return CoefficientSpectrum(coeffs);
	}
	CoefficientSpectrum max(const CoefficientSpectrum& rhs) const noexcept {
		std::array<Type, SAMPLES> coeffs;
		for (size_t i = 0u; i < SAMPLES; ++i)
			coeffs[i] = std::max(_coefficients[i], rhs._coefficients[i]);
		return CoefficientSpectrum(coeffs);
	}

protected:
	std::array<Type, SAMPLES> _coefficients;
};

template < std::floating_point T, size_t N >
CoefficientSpectrum<T, N> operator+(CoefficientSpectrum<T, N> lhs, const CoefficientSpectrum<T, N>& rhs) {
	lhs += rhs;
	return lhs;
}
template < std::floating_point T, size_t N >
CoefficientSpectrum<T, N> operator-(CoefficientSpectrum<T, N> lhs, const CoefficientSpectrum<T, N>& rhs) {
	lhs -= rhs;
	return lhs;
}
template < std::floating_point T, size_t N >
CoefficientSpectrum<T, N> operator*(CoefficientSpectrum<T, N> lhs, const CoefficientSpectrum<T, N>& rhs) {
	lhs *= rhs;
	return lhs;
}
template < std::floating_point T, size_t N >
CoefficientSpectrum<T, N> operator/(CoefficientSpectrum<T, N> lhs, const CoefficientSpectrum<T, N>& rhs) {
	lhs /= rhs;
	return lhs;
}
template < std::floating_point T, size_t N >
CoefficientSpectrum<T, N> operator*(CoefficientSpectrum<T, N> lhs, T rhs) {
	lhs *= rhs;
	return lhs;
}
template < std::floating_point T, size_t N >
CoefficientSpectrum<T, N> operator*(T lhs, CoefficientSpectrum<T, N> rhs) {
	rhs *= lhs;
	return rhs;
}
template < std::floating_point T, size_t N >
CoefficientSpectrum<T, N> operator/(CoefficientSpectrum<T, N> lhs, T rhs) {
	lhs /= rhs;
	return lhs;
}

template < std::floating_point T, size_t N >
CoefficientSpectrum<T, N> sqrt(CoefficientSpectrum<T, N> spectrum) {
	return spectrum.sqrt();
}
template < std::floating_point T, size_t N >
CoefficientSpectrum<T, N> pow(CoefficientSpectrum<T, N> spectrum, T exp) {
	return spectrum.pow(exp);
}
template < std::floating_point T, size_t N >
CoefficientSpectrum<T, N> exp(CoefficientSpectrum<T, N> spectrum) {
	return spectrum.exp();
}
template < std::floating_point T, size_t N >
CoefficientSpectrum<T, N> clamp(CoefficientSpectrum<T, N> spectrum, T min, T max) {
	return spectrum.clamp(min, max);
}

} // namespace spectral