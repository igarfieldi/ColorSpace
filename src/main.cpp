#include <iostream>

import math;
import colorspace;
import colorspace.xyz;

int main() {
	using SRgbfLinear = colorspace::Rgb<float, colorspace::SRGB<float>, true>;
	using AdobeRgbfLinear = colorspace::Rgb<float, colorspace::ADOBE_RGB_1998<float>, true>;
	using XYZf = colorspace::XYZ<float, colorspace::whitepoint::D50<float>>;


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
}