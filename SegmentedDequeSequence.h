#ifndef SegmentedDequeSequence_H
#define SegmentedDequeSequence_H

#include "lab_2/MutableArraySequence.h"
#include "MutableDequeSequence.h"
#include "lab_2/Sequence.h"
#include "lab_2/Errors.h"

#define SEGMENT_CAPACITY 16

template <typename T>
class SegmentedDequeSequence : public Sequence<T> {
private:
    MutableListSequence<MutableArraySequence<T>> segments;
    long total_length;
    long front_index;
    long back_segment_index;
    long back_index;

    void Add_front_segment() {
        MutableArraySequence<T> new_segment(SEGMENT_CAPACITY);
        segments.Prepend(new_segment);
        back_segment_index ++;
    }

    void Add_back_segment() {
        MutableArraySequence<T> new_segment(SEGMENT_CAPACITY);
        segments.Append(new_segment);
        back_segment_index ++;
    }

    void Quick_sort(long start, long end, MutableArraySequence<T> **cache) {
        if (start >= end) { return; }

        T middle = Get_fast((start + end) / 2, cache);
        long left = start;
        long right = end;
        while (left <= right) {
            while (Get_fast(left, cache) < middle) {
                 left ++;
            }
            while (Get_fast(right, cache) > middle) { 
                right --;
            }
            if (left <= right) {
                T temp = Get_fast(left, cache);
                Set_fast(left, Get_fast(right, cache), cache);
                Set_fast(right, temp, cache);
                left ++;
                right --;
            }
        }

        Quick_sort(start, right, cache);
        Quick_sort(left, end, cache);
    }

    T Get_fast(long global_index, MutableArraySequence<T> **cache) const {
        long relative_pos = front_index + global_index;
        return cache[relative_pos / SEGMENT_CAPACITY] -> Get(relative_pos % SEGMENT_CAPACITY);
    }

    void Set_fast(long global_index, T item, MutableArraySequence<T> **cache) {
        long relative_pos = front_index + global_index;
        cache[relative_pos / SEGMENT_CAPACITY] -> Set(relative_pos % SEGMENT_CAPACITY, item);
    }

public:
    SegmentedDequeSequence() {
        total_length = 0;
        back_segment_index = -1;
        front_index = -1;
        back_index = -1;
        Add_back_segment();
    }

    SegmentedDequeSequence(const SegmentedDequeSequence<T> &other) : segments(other.segments) {
        total_length = other.total_length;
        front_index = other.front_index;
        back_segment_index = other.back_segment_index;
        back_index = other.back_index;
    }

    ~SegmentedDequeSequence() override {}

    T Get_first() const override {
        if (total_length == 0) { throw EmptyCollection(); }
        return segments[0].Get(front_index);
    }

    T Get_last() const override {
        if (total_length == 0) { throw EmptyCollection(); }
        return segments[back_segment_index].Get(back_index);
    }

    T Get(long global_index) const override {
        if ((global_index < 0) || (global_index >= total_length)) { throw IndexOutOfRange(); }
        long relative_pos = front_index + global_index;
        return segments[relative_pos / SEGMENT_CAPACITY].Get(relative_pos % SEGMENT_CAPACITY);
    }

    long Get_length() const override { return total_length; }

    void Set(long global_index, T item) {
        if ((global_index < 0) || (global_index >= total_length)) { throw IndexOutOfRange(); }
        long relative_pos = front_index + global_index;
        segments[relative_pos / SEGMENT_CAPACITY].Set(relative_pos % SEGMENT_CAPACITY, item);
    }

    Sequence<T>* Append(T item) override {
        if (total_length == 0) {
            front_index = 0;
            back_index = 0;
            segments[0].Set(0, item);
            total_length = 1;
            return this;
        }
        if ((back_index + 1) >= SEGMENT_CAPACITY) {
            Add_back_segment();
            back_index = 0;
        } else {
            back_index ++;
        }
        segments[back_segment_index].Set(back_index, item);
        total_length ++;
        return this;
    }

    Sequence<T>* Prepend(T item) override {
        if (total_length == 0) {
            front_index = 0;
            back_index = 0;
            segments[0].Set(0, item);
            total_length = 1;
            return this;
        }
        if ((front_index - 1) < 0) {
            Add_front_segment();
            front_index = SEGMENT_CAPACITY - 1;
        } else {
            front_index --;
        }
        segments[0].Set(front_index, item);
        total_length ++;
        return this;
    }

    Sequence<T>* Insert_at(T item, long index) override {
        if ((index < 0) || (index > total_length)) { throw IndexOutOfRange(); }
        if (index == 0) { Prepend(item); return this; }
        if (index == total_length) { Append(item); return this; }
        long distance_to_front = index;
        long distance_to_back = total_length - index;
        if (distance_to_front <= distance_to_back) {
            Prepend(Get_first());
            for (long counter = 1; counter < index; counter ++) { Set(counter, Get(counter + 1)); }
            Set(index, item);
        } else {
            Append(Get_last());
            for (long counter = total_length - 2; counter > index; counter --) { Set(counter, Get(counter - 1)); }
            Set(index, item);
        }
        return this;
    }

    Sequence<T>* Get_subsequence(long start_index, long end_index) const override {
        if ((start_index < 0) || (end_index >= total_length)) { throw IndexOutOfRange(); }
        if (start_index > end_index) { throw IndexesTranslated(); }
        SegmentedDequeSequence<T> *result = new SegmentedDequeSequence<T>();
        Enumerator<T> enumerator = Get_enumerator();
        long counter = 0;
        while (enumerator.Move_next()) {
            if ((counter >= start_index) && (counter <= end_index)) { result -> Append(enumerator.Get_current()); }
            if (counter > end_index) { break; }
            counter ++;
        }
        return result;
    }

    Sequence<T>* Concat(Sequence<T> *other) override {
        if (other == nullptr) { throw NullPointerError(); }
        Enumerator<T> enumerator = other -> Get_enumerator();
        while (enumerator.Move_next()) { Append(enumerator.Get_current()); }
        return this;
    }

    Sequence<T>* Map(T (*function)(T)) const override {
        if (function == nullptr) { throw NullPointerError(); }
        SegmentedDequeSequence<T> *result = new SegmentedDequeSequence<T>();
        Enumerator<T> enumerator = Get_enumerator();
        while (enumerator.Move_next()) { result -> Append(function(enumerator.Get_current())); }
        return result;
    }

    Sequence<T>* Where(bool (*predicate)(T)) const override {
        if (predicate == nullptr) { throw NullPointerError(); }
        SegmentedDequeSequence<T> *result = new SegmentedDequeSequence<T>();
        Enumerator<T> enumerator = Get_enumerator();
        while (enumerator.Move_next()) {
            T val = enumerator.Get_current();
            if (predicate(val)) { result -> Append(val); }
        }
        return result;
    }

    T Reduce(T (*function)(T, T), T init) const override {
        if (function == nullptr) { throw NullPointerError(); }
        T result_val = init;
        Enumerator<T> enumerator = Get_enumerator();
        while (enumerator.Move_next()) { result_val = function(result_val, enumerator.Get_current()); }
        return result_val;
    }

    Option<T> Try_get_first(bool (*predicate)(T)) const override {
        if (predicate == nullptr) {
            if (total_length > 0) { return Option<T>(Get_first()); }
            return Option<T>();
        }
        Enumerator<T> enumerator = Get_enumerator();
        while (enumerator.Move_next()) {
            T val = enumerator.Get_current();
            if (predicate(val)) { return Option<T>(val); }
        }
        return Option<T>();
    }

    Option<T> Try_get_last(bool (*predicate)(T)) const override {
        if (predicate == nullptr) {
            if (total_length > 0) { return Option<T>(Get_last()); }
            return Option<T>();
        }
        Option<T> result;
        Enumerator<T> enumerator = Get_enumerator();
        while (enumerator.Move_next()) {
            T val = enumerator.Get_current();
            if (predicate(val)) { result = Option<T>(val); }
        }
        return result;
    }

    Sequence<T>* Slice(long start, long count, Sequence<T> *insert_seq = nullptr) override {
        long length = total_length;
        if ((start < 0) || (count < 0) || (start > length) || ((start + count) > length)) { throw IndexOutOfRange(); }
        SegmentedDequeSequence<T> *result = new SegmentedDequeSequence<T>();
        Enumerator<T> enumerator = Get_enumerator();
        for (long counter = 0; counter < start; counter ++) {
            enumerator.Move_next();
            result -> Append(enumerator.Get_current());
        }
        for (long skip_counter = 0; skip_counter < count; skip_counter ++) { enumerator.Move_next(); }
        if (insert_seq != nullptr) {
            Enumerator<T> insert_enum = insert_seq -> Get_enumerator();
            while (insert_enum.Move_next()) { result -> Append(insert_enum.Get_current()); }
        }
        while (enumerator.Move_next()) { result -> Append(enumerator.Get_current()); }
        return result;
    }

    Sequence<T>* Zip(Sequence<T> *other) const override {
        if (other == nullptr) { throw NullPointerError(); }
        SegmentedDequeSequence<T> *result = new SegmentedDequeSequence<T>();
        Enumerator<T> this_enum = Get_enumerator();
        Enumerator<T> other_enum = other -> Get_enumerator();
        while (this_enum.Move_next() && other_enum.Move_next()) {
            result -> Append(this_enum.Get_current());
            result -> Append(other_enum.Get_current());
        }
        return result;
    }

    Sequence<T>* Flat_map(Sequence<T>* (*function)(T)) const override {
        if (function == nullptr) { throw NullPointerError(); }
        SegmentedDequeSequence<T> *result = new SegmentedDequeSequence<T>();
        Enumerator<T> enumerator = Get_enumerator();
        while (enumerator.Move_next()) {
            Sequence<T> *mapped = function(enumerator.Get_current());
            if (mapped != nullptr) {
                Enumerator<T> map_enum = mapped -> Get_enumerator();
                while (map_enum.Move_next()) { result -> Append(map_enum.Get_current()); }
                delete mapped;
            }
        }
        return result;
    }

    bool Contains_subsequence(const Sequence<T> &sub) const {
        long sub_length = sub.Get_length();
        if (sub_length == 0) { return true; }
        if (sub_length > total_length) { return false; }
        for (long start = 0; start <= total_length - sub_length; start ++) {
            bool found = true;
            for (long offset = 0; offset < sub_length; offset ++) {
                if (Get(start + offset) != sub.Get(offset)) { found = false; break; }
            }
            if (found) { return true; }
        }
        return false;
    }

    SegmentedDequeSequence<T>* Sort() const {
        SegmentedDequeSequence<T> *result = new SegmentedDequeSequence<T>(*this);
        if (result -> total_length > 1) {
            long segment_count = result -> segments.Get_length();
            MutableArraySequence<T> **cache = new MutableArraySequence<T>*[segment_count];
            for (long i = 0; i < segment_count; i++) {
                cache[i] = &result -> segments[i];
            }

            result -> Quick_sort(0, result -> total_length - 1, cache);
            delete[] cache;
        }
        return result;
    }


    SegmentedDequeSequence<T>* Clone() const override { return new SegmentedDequeSequence<T>(*this); }

    Enumerator<T> Get_enumerator() const override {
        class SegmentedDequeEnumerator : public IEnumerator<T> {
        private:
            const SegmentedDequeSequence<T> *deque;
            long position;
            long length;
        public:
            SegmentedDequeEnumerator(const SegmentedDequeSequence<T> *d) : deque(d), position(-1), length(d -> total_length) {}
            bool Move_next() override {
                if ((position + 1) < length) { position ++; return true; }
                return false;
            }
            T Get_current() override { return deque -> Get(position); }
            void Reset() override { position = -1; }
        };
        return Enumerator<T>(new SegmentedDequeEnumerator(this));
    }

    bool operator==(const Sequence<T> &other) const override {
        if (total_length != other.Get_length()) { return false; }
        Enumerator<T> this_enum = Get_enumerator();
        Enumerator<T> other_enum = other.Get_enumerator();
        while (this_enum.Move_next() && other_enum.Move_next()) {
            if (this_enum.Get_current() != other_enum.Get_current()) { return false; }
        }
        return true;
    }
};

#endif //SegmentedDequeSequence_H