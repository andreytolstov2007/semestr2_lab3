#ifndef MutableListSequence_H
#define MutableListSequence_H

#include "DequeSequence.h"

template <typename T>
class MutableListSequence : public ListSequence<T> {
public:
    MutableListSequence() : ListSequence<T>() {}
    MutableListSequence(T *items_arr, long count) : ListSequence<T>(items_arr, count) {}
    MutableListSequence(const MutableListSequence<T> &other) : ListSequence<T>(other) {}

    MutableListSequence<T>* Clone() const override {
        return new MutableListSequence<T>(*this);
    }

    T& Get_ref(long index) {
        if ((index < 0) || (index >= this -> Get_length())) { throw IndexOutOfRange(); }
        return this -> items.Get_list_index_ref(index);
    }
};
#endif //MutableListSequence_H