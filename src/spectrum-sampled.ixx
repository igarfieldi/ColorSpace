module;

#include <concepts>
#include <cstddef>

export module spectrum:sampled;

import :coefficient;

namespace spectral {

constexpr size_t SAMPLE_COUNT = 60u;

template < std::floating_point T >
class SampledSpectrum : public CoefficientSpectrum<T, SAMPLE_COUNT> {
public:
	SampledSpectrum(T value) : CoefficientSpectrum(value) {}

private:

};

}