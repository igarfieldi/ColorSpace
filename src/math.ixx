module;

#include <algorithm>
#include <array>
#include <cassert>
#include <concepts>
#include <optional>
#include <string>

export module math;

export namespace math {

template < std::floating_point T >
class Mat3 {
public:
	using Type = T;
	static constexpr size_t ROWS = 3u;
	static constexpr size_t COLUMNS = 3u;

	static constexpr Mat3 diag(T value) noexcept {
		return Mat3(std::array<T, 9>{ { value, T(0), T(0), T(0), value, T(0), T(0), T(0), value }});
	}
	static constexpr Mat3 identity() noexcept {
		return diag(T(1));
	}
	explicit constexpr Mat3(T value = T(0)) noexcept {
		std::fill(std::begin(_data), std::end(_data), value);
	}
	explicit constexpr Mat3(std::array<T, 9> values) noexcept : _data(values) {}

	constexpr T determinant() const noexcept {
		return m00() * (m11() * m22() - m21() * m12())
			 + m01() * (m12() * m20() - m22() * m10())
			 + m02() * (m10() * m21() - m11() * m20());
	}

	constexpr Mat3 transpose() const noexcept {
		return Mat3({ {m00(), m10(), m20(), m01(), m11(), m21(), m02(), m12(), m22()} });
	}

	constexpr Mat3 adjugate() const noexcept {
		return Mat3(std::array<T, 9>{ {
				m11() * m22() - m12() * m21(), m02() * m21() - m01() * m22(), m01() * m12() - m02() * m11(),
				m12() * m20() - m10() * m22(), m00() * m22() - m02() * m20(), m02() * m10() - m00() * m12(),
				m10() * m21() - m11() * m20(), m01() * m20() - m00() * m21(), m00() * m11() - m01() * m10()
			} });
	}

	constexpr std::optional<Mat3> invert() const noexcept {
		const auto det = determinant();
		if (det == T(0))
			return std::nullopt;
		return adjugate() * (T(1) / det);
	}

	constexpr T& operator()(size_t row, size_t column) noexcept {
		assert(row < ROWS);
		assert(column < COLUMNS);
		return _data[row * COLUMNS + column];
	}
	constexpr const T& operator()(size_t row, size_t column) const noexcept {
		assert(row < ROWS);
		assert(column < COLUMNS);
		return _data[row * COLUMNS + column];
	}

	constexpr T& m00() noexcept { return _data[0]; }
	constexpr T& m01() noexcept { return _data[1]; }
	constexpr T& m02() noexcept { return _data[2]; }
	constexpr T& m10() noexcept { return _data[3]; }
	constexpr T& m11() noexcept { return _data[4]; }
	constexpr T& m12() noexcept { return _data[5]; }
	constexpr T& m20() noexcept { return _data[6]; }
	constexpr T& m21() noexcept { return _data[7]; }
	constexpr T& m22() noexcept { return _data[8]; }
	constexpr const T& m00() const noexcept { return _data[0]; }
	constexpr const T& m01() const noexcept { return _data[1]; }
	constexpr const T& m02() const noexcept { return _data[2]; }
	constexpr const T& m10() const noexcept { return _data[3]; }
	constexpr const T& m11() const noexcept { return _data[4]; }
	constexpr const T& m12() const noexcept { return _data[5]; }
	constexpr const T& m20() const noexcept { return _data[6]; }
	constexpr const T& m21() const noexcept { return _data[7]; }
	constexpr const T& m22() const noexcept { return _data[8]; }

	constexpr Mat3& operator+=(const Mat3& rhs) noexcept {
		for (size_t i = 0u; i < _data.size(); ++i)
			_data[i] += rhs._data[i];
		return *this;
	}
	constexpr Mat3& operator-=(const Mat3& rhs) noexcept {
		for (size_t i = 0u; i < _data.size(); ++i)
			_data[i] -= rhs._data[i];
		return *this;
	}

	constexpr Mat3& operator+=(T rhs) noexcept {
		for (size_t i = 0u; i < _data.size(); ++i)
			_data[i] += rhs;
		return *this;
	}
	constexpr Mat3& operator-=(T rhs) noexcept {
		for (size_t i = 0u; i < _data.size(); ++i)
			_data[i] -= rhs;
		return *this;
	}
	constexpr Mat3& operator*=(T rhs) noexcept {
		for (size_t i = 0u; i < _data.size(); ++i)
			_data[i] *= rhs;
		return *this;
	}
	constexpr Mat3& operator/=(T rhs) noexcept {
		for (size_t i = 0u; i < _data.size(); ++i)
			_data[i] /= rhs;
		return *this;
	}

	constexpr Mat3 operator-() const noexcept {
		return Mat3({ {-m00(), -m01(), -m02(), -m10(), -m11(), -m12(), -m20(), -m21(), -m22()} });
	}

private:
	std::array<T, 9> _data;
};

template < class T >
constexpr Mat3<T> operator+(Mat3<T> lhs, const Mat3<T>& rhs) noexcept {
	return lhs += rhs;
}

template < class T >
constexpr Mat3<T> operator-(Mat3<T> lhs, const Mat3<T>& rhs) noexcept {
	return lhs -= rhs;
}

template < class T >
constexpr Mat3<T> operator+(Mat3<T> lhs, T rhs) noexcept {
	return lhs += rhs;
}

template < class T >
constexpr Mat3<T> operator-(Mat3<T> lhs, T rhs) noexcept {
	return lhs -= rhs;
}

template < class T >
constexpr Mat3<T> operator*(Mat3<T> lhs, T rhs) noexcept {
	return lhs *= rhs;
}

template < class T >
constexpr Mat3<T> operator+(T lhs, Mat3<T> rhs) noexcept {
	return rhs += lhs;
}

template < class T >
constexpr Mat3<T> operator-(T lhs, const Mat3<T>& rhs) noexcept {
	return Mat3<T>(lhs) -= rhs;
}

template < class T >
constexpr Mat3<T> operator*(T lhs, Mat3<T> rhs) noexcept {
	return rhs *= lhs;
}

template < class T >
constexpr Mat3<T> operator*(const Mat3<T>& lhs, const Mat3<T>& rhs) noexcept {
	Mat3<T> res;
	for (size_t i = 0u; i < 3u; ++i)
		for (size_t j = 0u; j < 3u; ++j)
			for (size_t k = 0u; k < 3u; ++k)
				res(i, j) += lhs(i, k) * rhs(k, j);
	return res;
}

using Mat3f = Mat3<float>;
using Mat3d = Mat3<double>;

template < class T >
std::string to_string(const Mat3<T>& mat) {
	return std::string("[[") + std::to_string(mat.m00()) + "," + std::to_string(mat.m01()) + "," + std::to_string(mat.m02())
		+ "],[" + std::to_string(mat.m10()) + "," + std::to_string(mat.m11()) + "," + std::to_string(mat.m12())
		+ "],[" + std::to_string(mat.m20()) + "," + std::to_string(mat.m21()) + "," + std::to_string(mat.m22()) + "]]";
}

} //namespace math