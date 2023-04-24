module;

#include <cmath>
#include <concepts>

export module spectrum.blackbody;

namespace spectral::blackbody {

template < std::floating_point T >
inline constexpr T PLANCK(6.62607015);				//e-34	[J*s]
template < std::floating_point T >
inline constexpr T BOLTZMANN(1.380649);				//e-23	[J/K]
template < std::floating_point T >
inline constexpr T SPEED_OF_LIGHT(2.99792458);		//e8	[m]
template < std::floating_point T >
inline constexpr T WIEN_DISPLACEMENT(2.897771955);	//e-3	[m*K]

export template < std::floating_point T >
T compute_radiance(T wavelength_nm, T temperature_kelvin) noexcept {
	// Planck's law: B_v(v, T) = 2hv³/(c²e^(hv/(kT)) - 1)
	// Given wavelengths instead of frequencies this leads to
	// S_λ = 2*h*c²/(λ^5 * e^(h*c/(λ*k*T)) - 1)
	//, which computes the amount of energy rediated per unit time and unit area into a unit of solid angle perpendicular to the surface.
	const auto ePart = std::exp(PLANCK<T> * SPEED_OF_LIGHT<T> / (wavelength_nm * BOLTZMANN<T> * temperature_kelvin) * T(1e6));
	const auto nominator = T(2) * PLANCK<T> * SPEED_OF_LIGHT<T> * SPEED_OF_LIGHT<T>;
	const auto denominator = (wavelength_nm * wavelength_nm) * (wavelength_nm * wavelength_nm) * wavelength_nm * (ePart - T(1));
	return T(1e27) * nominator / denominator;
}

} // namespace spectral::blackbody