module;

#include <array>
#include <concepts>
#include <cstddef>

export module spectrum:shape;

namespace spectral {

export template < std::floating_point T, size_t N >
struct SpdShape {
	static constexpr SpdShape uniform_between(T start_nm, T end_nm) noexcept {
		static_assert(N > 0);
		if constexpr (N == 1) {
			return SpdShape{ { T(0.5)* (end_nm - start_nm) }};
		} else {
			std::array<T, N> wavelengths_nm;
			const auto interval = (end_nm - start_nm) / static_cast<T>(N - 1u);
			wavelengths_nm[0] = start_nm;
			wavelengths_nm[N - 1u] = end_nm;
			for (size_t i = 1u; i + 1u < N; ++i)
				wavelengths_nm[i] = start_nm + i * interval;
			return SpdShape{wavelengths_nm};
		}
	}

	static constexpr SpdShape uniform_interval(T start_nm, T interval_nm) noexcept {
		static_assert(N > 0);
		if constexpr (N == 1) {
			return SpdShape{ { start_nm } };
		} else {
			std::array<T, N> wavelengths_nm;
			wavelengths_nm[0] = start_nm;
			for (size_t i = 1u; i < N; ++i)
				wavelengths_nm[i] = start_nm + i * interval_nm;
			return SpdShape{ wavelengths_nm };
		}
	}

	constexpr bool is_sorted() const noexcept {
		if constexpr (N <= 1) {
			return true;
		} else {
			for (size_t i = 1u; i < wavelengths_nm.size(); ++i)
				if (wavelengths_nm[i] <= wavelengths_nm[i - 1u])
					return false;
			return true;
		}
	}

	constexpr bool is_uniform() const noexcept {
		if constexpr (N <= 2) {
			return true;
		} else {
			const T distance = wavelengths_nm[1] - wavelengths_nm[0];
			for (size_t i = 2u; i < wavelengths_nm.size(); ++i)
				if (wavelengths_nm[i] - wavelengths_nm[i - 1u] != distance)
					return false;
			return true;
		}
	}

	std::array<T, N> wavelengths_nm;
};

} // namespace spectral