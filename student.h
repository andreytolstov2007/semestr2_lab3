#ifndef Student_H
#define Student_H

#include "String.h"

class Student {
private:
    String first_name;
    String middle_name;
    String last_name;
    long id;
    long birth_year;

public:
    Student() : first_name(), middle_name(), last_name(), id(0), birth_year(0) {}

    Student(const String &first, const String &middle, const String &last, long student_id, long year)
        : first_name(first), middle_name(middle), last_name(last), id(student_id), birth_year(year) {}

    String Get_first_name() const { return first_name; }

    String Get_middle_name() const { return middle_name; }

    String Get_last_name() const { return last_name; }

    String Get_full_name() const {
        return last_name + String(" ") + first_name + String(" ") + middle_name;
    }

    long Get_id() const { return id; }

    long Get_birth_year() const { return birth_year; }

    bool operator==(const Student &other) const {
        return (id == other.id);
    }

    bool operator!=(const Student &other) const {
        return !(*this == other);
    }

    static Student Read();
};

std::ostream& operator<<(std::ostream &os, const Student &value);


#endif //Student_H