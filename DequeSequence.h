#ifndef ListSequence_H
#define ListSequence_H

#include "lab_2/Sequence.h"
#include "Deque.h"

template <typename T>
class ListSequence : public Sequence<T> {
private:
    LinkedList<T> items;

protected:
    virtual ListSequence<T>* Instance() { return this; }

public:
    ListSequence() {}

    ListSequence(T *items_arr, long count) : items(items_arr, count) {}

    ListSequence(const ListSequence<T> &other) : items(other.items) {}

    ~ListSequence() override {}

    T Get_first() const override {
        if (Get_length() == 0) { throw EmptyCollection(); }
        return items.Get_first();
    }

    T Get_last() const override {
        if (Get_length() == 0) { throw EmptyCollection(); }
        return items.Get_last();
    }

    T Get(long index) const override {
        if ((index < 0) || (index >= Get_length())) { throw IndexOutOfRange(); }
        return items.Get_list_index(index);
    }

    long Get_length() const override { return items.Get_length(); }

    Sequence<T>* Get_subsequence(long start_index, long end_index) const override {
        if ((start_index < 0) || (end_index >= Get_length())) { throw IndexOutOfRange(); }
        if (start_index > end_index) { throw IndexesTranslated(); }

        ListSequence<T> *result = new ListSequence<T>();
        Enumerator<T> enumerator = items.Get_enumerator();
        for (long counter = 0; counter < start_index; counter ++) {
            enumerator.Move_next();
        }
        for (long counter = start_index; counter <= end_index; counter ++) {
            result -> items.Append(enumerator.Get_current());
            enumerator.Move_next();
        }
        return result;
    }

    ListSequence<T>* Clone() const override { return new ListSequence<T>(*this); }

    Sequence<T>* Append(T item) override {
        ListSequence<T> *result = Instance();
        result -> items.Append(item);
        return result;
    }

    Sequence<T>* Prepend(T item) override {
        ListSequence<T> *result = Instance();
        result -> items.Prepend(item);
        return result;
    }

    Sequence<T>* Insert_at(T item, long index) override {
        if ((index < 0) || (index > Get_length())) { throw IndexOutOfRange(); }

        ListSequence<T> *result = Instance();
        result -> items.Insert_at(item, index);
        return result;
    }

    Sequence<T>* Concat(Sequence<T> *other) override {
        if (other == nullptr) { throw NullPointerError(); }

        ListSequence<T> *result = Instance();
        Enumerator<T> enumerator = other -> Get_enumerator();
        while (enumerator.Move_next()) {
            result -> items.Append(enumerator.Get_current());
        }
        return result;
    }

    Sequence<T>* Map(T (*function)(T)) const override {
        if (function == nullptr) { throw NullPointerError(); }

        ListSequence<T> *result = new ListSequence<T>();
        Enumerator<T> enumerator = items.Get_enumerator();
        while (enumerator.Move_next()) {
            T value = function(enumerator.Get_current());
            result -> items.Append(value);
        }
        return result;
    }

    Sequence<T>* Where(bool (*predicate)(T)) const override {
        if (predicate == nullptr) { throw NullPointerError(); }

        ListSequence<T> *result = new ListSequence<T>();
        Enumerator<T> enumerator = items.Get_enumerator();
        while (enumerator.Move_next()) {
            T value = enumerator.Get_current();
            if (predicate(value)) {
                result -> items.Append(value);
            }
        }
        return result;
    }

    T Reduce(T (*function)(T, T), T init) const override {
        if (function == nullptr) { throw NullPointerError(); }

        T result_val = init;
        Enumerator<T> enumerator = items.Get_enumerator();
        while (enumerator.Move_next()) {
            result_val = function(result_val, enumerator.Get_current());
        }
        return result_val;
    }

    Option<T> Try_get_first(bool (*predicate)(T)) const override {
        if (predicate == nullptr) {
            if (Get_length() > 0) {
                return Option<T>(Get_first());
            }
            return Option<T>();
        }

        Enumerator<T> enumerator = items.Get_enumerator();
        while (enumerator.Move_next()) {
            T value = enumerator.Get_current();
            if (predicate(value)) {
                return Option<T>(value);
            }
        }
        return Option<T>();
    }

    Option<T> Try_get_last(bool (*predicate)(T)) const override {
        if (predicate == nullptr) {
            if (Get_length() > 0) {
                return Option<T>(Get_last());
            }
            return Option<T>();
        }

        T found_value;
        bool found = false;
        Enumerator<T> enumerator = items.Get_enumerator();
        while (enumerator.Move_next()) {
            T value = enumerator.Get_current();
            if (predicate(value)) {
                found_value = value;
                found = true;
            }
        }
        if (found) {
            return Option<T>(found_value);
        }
        return Option<T>();
    }

    Sequence<T>* Slice(long start, long count, Sequence<T> *insert_seq = nullptr) override {
        ListSequence<T> *result = Instance();
        long length = result -> Get_length();
        if ((start < 0) || (count < 0) || (start > length) || (start + count > length)) { throw IndexOutOfRange(); }

        LinkedList<T> temp_list;
        Enumerator<T> enumerator = result -> items.Get_enumerator();
        for (long counter = 0; counter < start; counter ++) {
            enumerator.Move_next();
            temp_list.Append(enumerator.Get_current());
        }
        for (long counter = 0; counter < count; counter ++) { enumerator.Move_next(); }
        if (insert_seq != nullptr) {
            Enumerator<T> insert_enum = insert_seq -> Get_enumerator();
            while (insert_enum.Move_next()) { temp_list.Append(insert_enum.Get_current()); }
        }
        while (enumerator.Move_next()) { temp_list.Append(enumerator.Get_current()); }
        result -> items = temp_list;
        return result;
    }

    Sequence<T>* Zip(Sequence<T> *other) const override {
        if (other == nullptr) { throw NullPointerError(); }

        ListSequence<T> *result = new ListSequence<T>();
        Enumerator<T> this_enum = items.Get_enumerator();
        Enumerator<T> other_enum = other -> Get_enumerator();
        while (this_enum.Move_next() && other_enum.Move_next()) {
            result -> items.Append(this_enum.Get_current());
            result -> items.Append(other_enum.Get_current());
        }
        return result;
    }

    Sequence<T>* Flat_map(Sequence<T>* (*function)(T)) const override {
        if (function == nullptr) { throw NullPointerError(); }

        ListSequence<T> *result = new ListSequence<T>();
        Enumerator<T> enumerator = items.Get_enumerator();
        while (enumerator.Move_next()) {
            Sequence<T> *mapped = function(enumerator.Get_current());
            if (mapped != nullptr) {
                Enumerator<T> map_enum = mapped -> Get_enumerator();
                while (map_enum.Move_next()) {
                    result -> items.Append(map_enum.Get_current());
                }
                delete mapped;
            }
        }
        return result;
    }

    Enumerator<T> Get_enumerator() const override { return items.Get_enumerator(); }

    bool operator==(const Sequence<T> &other) const override {
        if (Get_length() != other.Get_length()) { return false; }

        Enumerator<T> this_enum = items.Get_enumerator();
        Enumerator<T> other_enum = other.Get_enumerator();
        while (this_enum.Move_next() && other_enum.Move_next()) {
            if (this_enum.Get_current() != other_enum.Get_current()) {
                return false;
            }
        }
        return true;
    }

    T& operator[](long index) {
        if ((index < 0) || (index >= Get_length())) { throw IndexOutOfRange(); }
        return items[index];
    }
    
    const T& operator[](long index) const {
        if ((index < 0) || (index >= Get_length())) { throw IndexOutOfRange(); }
        return items[index];
    }
};
#endif //ListSequence_H