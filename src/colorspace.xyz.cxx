module colorspace.xyz;
import colorspace;

namespace colorspace {

template class XYZ<float, whitepoint::D50<float>>;
template class XYZ<float, whitepoint::D55<float>>;
template class XYZ<float, whitepoint::D60<float>>;
template class XYZ<float, whitepoint::D65<float>>;
template class XYZ<float, whitepoint::DCI<float>>;
template class XYZ<float, whitepoint::ACES<float>>;
template class XYZ<double, whitepoint::D50<double>>;
template class XYZ<double, whitepoint::D55<double>>;
template class XYZ<double, whitepoint::D60<double>>;
template class XYZ<double, whitepoint::D65<double>>;
template class XYZ<double, whitepoint::DCI<double>>;
template class XYZ<double, whitepoint::ACES<double>>;

} // namespace colorspace