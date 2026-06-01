#include "Teacher.h"

std::ostream& operator<<(std::ostream &os, const Teacher &value) {
    os << value.Get_full_name().Get_c_str() << " (id=" << value.Get_id() << ")";
    return os;
}

Teacher Teacher::Read() {
    std::string first, middle, last, dept;
    long teacher_id;
    std::cout << "  first name: "; std::cin >> first;
    std::cout << "  middle name: "; std::cin >> middle;
    std::cout << "  last name: "; std::cin >> last;
    std::cout << "  id: "; std::cin >> teacher_id;
    std::cout << "  department: "; std::cin >> dept;
    return Teacher(String(first.c_str()), String(middle.c_str()), String(last.c_str()), teacher_id, String(dept.c_str()));
}