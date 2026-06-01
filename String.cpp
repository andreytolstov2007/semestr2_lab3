#include "String.h"

std::ostream& operator<<(std::ostream &os, const String &value) {
    os << value.Get_c_str();
    return os;
}

String String::Read() {
    std::string input;
    std::cout << "  string: ";
    std::cin >> input;
    return String(input.c_str());
}