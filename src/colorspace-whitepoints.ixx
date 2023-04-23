module;

#include <concepts>

export module colorspace:whitepoints;
import chromaticity;

export namespace colorspace::whitepoint {

export template < std::floating_point T >
inline constexpr XYY<T> D50{ T(0.3457), T(0.3585), T(1) };
export template < std::floating_point T >
inline constexpr XYY<T> D55{ T(0.33243), T(0.34744), T(1) };
export template < std::floating_point T >
inline constexpr XYY<T> D60{ T(0.32168), T(0.33767), T(1) };
export template < std::floating_point T >
inline constexpr XYY<T> D65{ T(0.3127), T(0.329), T(1) };
export template < std::floating_point T >
inline constexpr XYY<T> DCI{ T(0.314), T(0.351), T(1) };
export template < std::floating_point T >
inline constexpr XYY<T> ACES{ T(0.32168), T(0.33767), T(1) };

} // namespace colorspace::whitepoint