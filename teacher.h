#ifndef Teacher_H
#define Teacher_H

#include "String.h"

class Teacher {
private:
    String first_name;
    String middle_name;
    String last_name;
    long id;
    String department;

public:
    Teacher() : first_name(), middle_name(), last_name(), id(0), department() {}

    Teacher(const String &first, const String &middle, const String &last, long teacher_id, const String &dept)
        : first_name(first), middle_name(middle), last_name(last), id(teacher_id), department(dept) {}

    String Get_first_name() const { return first_name; }

    String Get_middle_name() const { return middle_name; }

    String Get_last_name() const { return last_name; }

    String Get_full_name() const {
        return last_name + String(" ") + first_name + String(" ") + middle_name;
    }

    long Get_id() const { return id; }

    String Get_department() const { return department; }

    bool operator==(const Teacher &other) const {
        return (id == other.id);
    }

    bool operator!=(const Teacher &other) const {
        return !(*this == other);
    }

    static Teacher Read();
};

std::ostream& operator<<(std::ostream &os, const Teacher &value);
#endif //Teacher_H