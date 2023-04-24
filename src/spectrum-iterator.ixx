module;

#include <concepts>
#include <cstddef>
#include <cstdint>
#include <iterator>
#include <tuple>
#include <type_traits>

export module spectrum:iterator;
import :shape;

namespace spectral {

export template < class T >
struct SpdSample {
	T wavelength;
	T value;
};

template < std::floating_point T, size_t N, SpdShape<T, N> S, bool C >
class SpdIterator {
public:
	using Type = T;
	static constexpr size_t WAVELENGTH_COUNT = N;
	static constexpr size_t SAMPLE_COUNT = WAVELENGTH_COUNT - 1;
	static constexpr SpdShape<T, WAVELENGTH_COUNT> SHAPE = S;
	static constexpr bool IS_CONST = C;
	static constexpr bool IS_UNIFORM = SHAPE.is_uniform();

	static_assert(SHAPE.is_sorted(), "The SPD shape (aka. its wavelengths must be sorted in ascending order");

	using iterator_category = std::input_iterator_tag;
	using difference_type = std::ptrdiff_t;
	using value_type = SpdSample<T>;
	using reference = SpdSample<std::conditional_t<IS_CONST, T, T&>>;

	using array_type = std::conditional_t<IS_CONST, const std::array<T, SAMPLE_COUNT>&, std::array<T, SAMPLE_COUNT>&>;

	static SpdIterator begin(array_type coefficients) noexcept {
		return SpdIterator(coefficients, 0u);
	}
	static SpdIterator end(array_type coefficients) noexcept {
		return SpdIterator(coefficients, coefficients.size());
	}

	constexpr bool operator==(const SpdIterator& rhs) const noexcept {
		return &_coefficients == &rhs._coefficients && _index == rhs._index;
	}
	constexpr bool operator!=(const SpdIterator& rhs) const noexcept {
		return &_coefficients != &rhs._coefficients || _index != rhs._index;
	}

	constexpr reference operator*() const noexcept { return reference( S.wavelengths_nm[_index] + T(0.5) * (S.wavelengths_nm[_index + 1] - S.wavelengths_nm[_index]),
																	  _coefficients[_index]); }
	constexpr SpdIterator& operator++() noexcept { ++_index; return *this; }
	constexpr SpdIterator operator++(int) noexcept { SpdIterator tmp(*this); ++(*this); return tmp; }
	constexpr SpdIterator& operator--() noexcept { --_index; return *this; }
	constexpr SpdIterator operator--(int) noexcept { SpdIterator tmp(*this); --(*this); return tmp; }

private:
	SpdIterator(array_type coefficients, size_t index) noexcept :
		_coefficients(coefficients),
		_index(index) {}

	array_type _coefficients;
	size_t _index;
};

} // namespace spectral