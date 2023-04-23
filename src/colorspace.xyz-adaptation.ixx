module;

#include <concepts>

export module colorspace.xyz:adaptation;
import :cs;
import chromaticity;
import math;

namespace colorspace {

export template < std::floating_point T, XYY<T> S, XYY<T> D >
consteval math::Mat3<T> adaptation_cat_02() noexcept {
	using Mat = math::Mat3<T>;

	if (S == D)
		return Mat::identity();

	constexpr Mat m_cat02{ std::array<T, 9>{{
		T(0.7328), T(0.4296), T(-0.1624),
		T(-0.7036), T(1.6975), T(0.0061),
		T(0.0030), T(0.0136), T(0.9834)
	}} };
	constexpr auto m_cat02_inv = m_cat02.invert();

	constexpr auto s = m_cat02 * XYZ<T, S>(S);
	constexpr auto d = m_cat02 * XYZ<T, D>(D);

	constexpr Mat trafo(std::array<T, 9>{{
		d.x() / s.x(), T(0), T(0),
		T(0), d.y() / s.y(), T(0),
		T(0), T(0), d.z() / s.z()
	}});

	return m_cat02_inv.value() * trafo * m_cat02;
}

} // namespace colorspace 