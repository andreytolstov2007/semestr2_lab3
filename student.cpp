#include "Student.h"

std::ostream& operator<<(std::ostream &os, const Student &value) {
    os << value.Get_full_name().Get_c_str() << " (id=" << value.Get_id() << ")";
    return os;
}

Student Student::Read() {
    std::string first, middle, last;
    long student_id, year;
    std::cout << "  first name: "; std::cin >> first;
    std::cout << "  middle name: "; std::cin >> middle;
    std::cout << "  last name: "; std::cin >> last;
    std::cout << "  id: "; std::cin >> student_id;
    std::cout << "  birth year: "; std::cin >> year;
    return Student(String(first.c_str()), String(middle.c_str()), String(last.c_str()), student_id, year);
}