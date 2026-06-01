#ifndef String_H
#define String_H

#include <cstring>
#include <iostream>

class String {
private:
    char *data;
    long length;

public:
    String() {
        length = 0;
        data = new char[1];
        data[0] = '\0';
    }

    String(const char *str) {
        if (str == nullptr) {
            length = 0;
            data = new char[1];
            data[0] = '\0';
        }
        else {
            length = std::strlen(str);
            data = new char[length + 1];
            std::strcpy(data, str);
        }
    }

    String(const String &other) {
        length = other.length;
        data = new char[length + 1];
        std::strcpy(data, other.data);
    }

    ~String() {
        delete[] data;
    }

    String& operator=(const String &other) {
        if (this != &other) {
            delete[] data;
            length = other.length;
            data = new char[length + 1];
            std::strcpy(data, other.data);
        }
        return *this;
    }

    const char* Get_c_str() const { return data; }

    long Get_length() const { return length; }

    bool operator==(const String &other) const {
        return std::strcmp(data, other.data) == 0;
    }

    bool operator!=(const String &other) const {
        return !(*this == other);
    }

    bool operator<(const String &other) const {
        return std::strcmp(data, other.data) < 0;
    }

    String operator+(const String &other) const {
        char *new_data = new char[length + other.length + 1];
        std::strcpy(new_data, data);
        std::strcat(new_data, other.data);
        String result(new_data);
        delete[] new_data;
        return result;
    }

    static String Read();
};

std::ostream& operator<<(std::ostream &os, const String &value);
#endif //String_H