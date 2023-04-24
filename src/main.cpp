#include <iostream>

import math;
import colorspace;
import colorspace.xyz;
import spectrum;

int main() {
	using SRgbfLinear = colorspace::Rgb<float, colorspace::SRGB<float>, true>;
	using AdobeRgbfLinear = colorspace::Rgb<float, colorspace::ADOBE_RGB_1998<float>, true>;
	using XYZf = colorspace::XYZ<float, colorspace::whitepoint::D65<float>>;

	constexpr auto shape = spectral::SpdShape<float, 60>::uniform_between(320.f, 720.f);
	const auto spd = spectral::Spd<float, 60, shape>::blackbody(5000.f);
	for (const auto& val : spd)
		printf("Wavelength: %fnm, value: %f\n", val.wavelength, val.value);

	const auto [val, wv] = spd.max();
	std::cout << "Max. wavelength: " << wv << " (value: " << val << ")" << std::endl;

	const XYZf xyz(spd);
	const SRgbfLinear srgb(xyz);
	const auto srgb_norm = srgb.normalize();
	const auto srgb_encoded = srgb_norm.encode();

	const AdobeRgbfLinear adobe(srgb_norm);
	const auto adobe_encoded = adobe.encode();

	std::cout << "XYZ:               " << colorspace::to_string(xyz) << std::endl;
	std::cout << "sRGB:              " << colorspace::to_string(srgb) << std::endl;
	std::cout << "sRGB normalized:   " << colorspace::to_string(srgb_norm) << std::endl;
	std::cout << "sRGB encoded:      " << colorspace::to_string(srgb_encoded) << std::endl;
	std::cout << "ADOBE RGB:         " << colorspace::to_string(adobe) << std::endl;
	std::cout << "ADOBE RGB encoded: " << colorspace::to_string(adobe_encoded) << std::endl;
}