#ifndef ImmutableDecueSequence_H
#define ImmutableDecueSequence_H

#include "DequeSequence.h"

template <typename T>
class ImmutableListSequence : public ListSequence<T> {
public:
    ImmutableListSequence() : ListSequence<T>() {}
    ImmutableListSequence(T *items_arr, long count) : ListSequence<T>(items_arr, count) {}
    ImmutableListSequence(const ImmutableListSequence<T> &other) : ListSequence<T>(other) {}

    ImmutableListSequence<T>* Clone() const override {
        return new ImmutableListSequence<T>(*this);
    }

protected:
    ImmutableListSequence<T>* Instance() override {
        return this -> Clone();
    }
};
#endif //ImmutableDecueSequence_H
