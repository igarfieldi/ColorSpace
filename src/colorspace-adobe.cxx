module colorspace:adobe;

import colorspace;

namespace colorspace {

template class Rgb<float, ADOBE_RGB_1998<float>, true>;
template class Rgb<float, ADOBE_RGB_1998<float>, false>;
template class Rgb<double, ADOBE_RGB_1998<double>, true>;
template class Rgb<double, ADOBE_RGB_1998<double>, false>;

} // namespace colorspace