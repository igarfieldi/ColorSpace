module;

#include <array>
#include <concepts>
#include <string>

export module colorspace.xyz:cs;
import chromaticity;
import math;

namespace colorspace {

export template < std::floating_point T, XYY<T> W >
class XYZ {
public:
	using Type = T;
	static constexpr XYY<T> WHITE_POINT = W;

	constexpr explicit XYZ(T value = T(0)) : XYZ(value, value, value) {}
	constexpr XYZ(T x, T y, T z) : XYZ(std::array<T, 3>{ { x, y, z }}) {}
	constexpr XYZ(std::array<T, 3> values) : _values{ values } {}
	constexpr explicit XYZ(const XYY<T>& xyy) :
		XYZ(xyy.x* xyy.Y / xyy.y, xyy.Y, (T(1) - xyy.x - xyy.y)* xyy.Y / xyy.y) {}

	constexpr const T& x() const noexcept { return _values[0]; }
	constexpr const T& y() const noexcept { return _values[1]; }
	constexpr const T& z() const noexcept { return _values[2]; }
	constexpr T& x() noexcept { return _values[0]; }
	constexpr T& y() noexcept { return _values[1]; }
	constexpr T& z() noexcept { return _values[2]; }

	constexpr const std::array<T, 3>& raw() const noexcept { return _values; }
	constexpr std::array<T, 3>& raw() noexcept { return _values; }

private:
	std::array<T, 3> _values;
};

export template < class T, XYY<T> W >
constexpr XYZ<T, W> operator*(const math::Mat3<T>& lhs, const XYZ<T, W>& rhs) noexcept {
	return XYZ<T, W>(
		lhs.m00() * rhs.x() + lhs.m01() * rhs.y() + lhs.m02() * rhs.z(),
		lhs.m10() * rhs.x() + lhs.m11() * rhs.y() + lhs.m12() * rhs.z(),
		lhs.m20() * rhs.x() + lhs.m21() * rhs.y() + lhs.m22() * rhs.z()
	);
}

export template < class T, XYY<T> W >
std::string to_string(const XYZ<T, W>& xyz) {
	return std::string("[") + std::to_string(xyz.x()) + "," + std::to_string(xyz.y()) + "," + std::to_string(xyz.z()) + "]";
}

} // namespace colorspace