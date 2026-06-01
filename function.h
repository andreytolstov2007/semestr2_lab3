#ifndef Function_H
#define Function_H

#include "lab_2/Errors.h"

template <typename T>
class Function {
private:
    T (*function_pointer)(T);

public:
    Function() : function_pointer(nullptr) {}

    explicit Function(T (*func)(T)) : function_pointer(func) {}

    T Execute(T argument) const {
        if (function_pointer == nullptr) { throw NullPointerError(); }
        return function_pointer(argument);
    }

    T operator()(T argument) const {
        return Execute(argument);
    }

    bool operator==(const Function<T> &other) const {
        return function_pointer == other.function_pointer;
    }

    bool operator!=(const Function<T> &other) const {
        return !(*this == other);
    }
};

#endif //Function_H