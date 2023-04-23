module colorspace:dcip3;

import colorspace;

namespace colorspace {

template class Rgb<float, DCI_P3<float>, true>;
template class Rgb<float, DCI_P3<float>, false>;
template class Rgb<double, DCI_P3<double>, true>;
template class Rgb<double, DCI_P3<double>, false>;

template class Rgb<float, DCI_P3_D65<float>, true>;
template class Rgb<float, DCI_P3_D65<float>, false>;
template class Rgb<double, DCI_P3_D65<double>, true>;
template class Rgb<double, DCI_P3_D65<double>, false>;

} // namespace colorspace