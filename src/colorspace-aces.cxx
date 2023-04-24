module colorspace:aces;

import colorspace;

namespace colorspace {

template class Rgb<float, ACES<float>, true>;
template class Rgb<float, ACES<float>, false>;
template class Rgb<double, ACES<double>, true>;
template class Rgb<double, ACES<double>, false>;

} // namespace colorspace