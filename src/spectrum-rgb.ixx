module;

#include <concepts>

export module spectrum:rgb;
import :coefficient;

namespace spectral {

template < std::floating_point T >
class Rgb : public CoefficientSpectrum<T, 3u> {
public:
	Rgb (T value) : CoefficientSpectrum(value) {}
	Rgb (T r, T g, T b) : CoefficientSpectrum({ {r, g, b} }) {}

	T& r() noexcept { return this->_coefficients[0]; }
	T& g() noexcept { return this->_coefficients[1]; }
	T& b() noexcept { return this->_coefficients[2]; }
	const T& r() const noexcept { return this->_coefficients[0]; }
	const T& g() const noexcept { return this->_coefficients[1]; }
	const T& b() const noexcept { return this->_coefficients[2]; }

	T luminance() const noexcept {
		return r() * T(0.212671) + g() * T(0.71516) + b() * T(0.072169);
	}

private:

};

} // namespace spectral