#include <iostream>

import math;
import colorspace;
import colorspace.xyz;
import spectrum;

int main() {
	using SRgbfLinear = colorspace::Rgb<float, colorspace::SRGB<float>, true>;
	using AdobeRgbfLinear = colorspace::Rgb<float, colorspace::ADOBE_RGB_1998<float>, true>;
	using XYZf = colorspace::XYZ<float, colorspace::whitepoint::D65<float>>;


	SRgbfLinear rgb(0.5f, 0.5f, 0.5f);
	auto rgb_encoded = rgb.encode();
	auto rgb_decoded = rgb_encoded.decode();


	const XYZf xyz(rgb);
	const AdobeRgbfLinear conv_rgb(rgb);

	std::cout << colorspace::to_string(rgb) << std::endl;
	std::cout << colorspace::to_string(rgb_encoded) << std::endl;
	std::cout << colorspace::to_string(rgb_decoded) << std::endl;
	std::cout << colorspace::to_string(xyz) << std::endl;
	std::cout << colorspace::to_string(conv_rgb) << std::endl;

	constexpr auto shape = spectral::SpdShape<float, 60>::uniform_between(320.f, 720.f);
	const auto spd = spectral::Spd<float, 60, shape>::blackbody(5000.f);
	for (const auto& val : spd)
		printf("Wavelength: %fnm, value: %f\n", val.second, val.first);

	const auto xyz2 = spd.to_xyz<colorspace::whitepoint::D65<float>>();
	const SRgbfLinear rgb2(xyz2);
	const auto rgb2norm = rgb2.normalize();
	const auto rgb2encoded = rgb2norm.encode();

	std::cout << colorspace::to_string(xyz2) << std::endl;
	std::cout << colorspace::to_string(rgb2) << std::endl;
	std::cout << colorspace::to_string(rgb2norm) << std::endl;
	std::cout << colorspace::to_string(rgb2encoded) << std::endl;


	printf("Done\n");
}