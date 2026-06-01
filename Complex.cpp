#include "Complex.h"

std::ostream& operator<<(std::ostream &os, const Complex &value) {
    os << "(" << value.Get_real() << " + " << value.Get_imaginary() << "i)";
    return os;
}

Complex Complex::Read() {
    double real_val, imag_val;
    std::cout << "  real: ";
    std::cin >> real_val;
    std::cout << "  imaginary: ";
    std::cin >> imag_val;
    return Complex(real_val, imag_val);
}