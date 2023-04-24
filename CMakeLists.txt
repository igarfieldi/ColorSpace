cmake_minimum_required(VERSION 3.26.0)

project(BlackBodyColorCalculator CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "2182bf5c-ef0d-489a-91da-49dbc3090d2a")
set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP 1)

add_library(Spectrum  STATIC)
target_sources(Spectrum
	PUBLIC
		FILE_SET cxx_modules TYPE CXX_MODULES FILES
		${CMAKE_CURRENT_SOURCE_DIR}/src/chromaticity.ixx
		${CMAKE_CURRENT_SOURCE_DIR}/src/colorspace.ixx
		${CMAKE_CURRENT_SOURCE_DIR}/src/colorspace-adobe.ixx
		${CMAKE_CURRENT_SOURCE_DIR}/src/colorspace-aces.ixx
		${CMAKE_CURRENT_SOURCE_DIR}/src/colorspace-dcip3.ixx
		${CMAKE_CURRENT_SOURCE_DIR}/src/colorspace-rgb.ixx
		${CMAKE_CURRENT_SOURCE_DIR}/src/colorspace-srgb.ixx
		${CMAKE_CURRENT_SOURCE_DIR}/src/colorspace-whitepoints.ixx
		${CMAKE_CURRENT_SOURCE_DIR}/src/colorspace.xyz.ixx
		${CMAKE_CURRENT_SOURCE_DIR}/src/colorspace.xyz-adaptation.ixx
		${CMAKE_CURRENT_SOURCE_DIR}/src/colorspace.xyz-cs.ixx
		${CMAKE_CURRENT_SOURCE_DIR}/src/colorspace.xyz.aliases.ixx
		${CMAKE_CURRENT_SOURCE_DIR}/src/math.ixx
		${CMAKE_CURRENT_SOURCE_DIR}/src/spectrum.ixx
		${CMAKE_CURRENT_SOURCE_DIR}/src/spectrum-cie.ixx
		${CMAKE_CURRENT_SOURCE_DIR}/src/spectrum-iterator.ixx
		${CMAKE_CURRENT_SOURCE_DIR}/src/spectrum-shape.ixx
		${CMAKE_CURRENT_SOURCE_DIR}/src/spectrum-spd.ixx
		${CMAKE_CURRENT_SOURCE_DIR}/src/spectrum.blackbody.ixx
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/src/colorspace-adobe.cxx
		${CMAKE_CURRENT_SOURCE_DIR}/src/colorspace-dcip3.cxx
		${CMAKE_CURRENT_SOURCE_DIR}/src/colorspace-srgb.cxx
		${CMAKE_CURRENT_SOURCE_DIR}/src/colorspace.xyz.cxx)

add_executable(SpectrumTest
	${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
set_target_properties(SpectrumTest PROPERTIES
	CXX_STANDARD 20)
target_link_libraries(SpectrumTest Spectrum)