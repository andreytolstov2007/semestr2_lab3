#include <iostream>
#include <limits>
#include "lab_2/MutableArraySequence.h"
#include "SegmentedDequeSequence.h"
#include "Complex.h"
#include "String.h"
#include "Student.h"
#include "Teacher.h"

void Run_tests();

long Read_long(const std::string &prompt) {
    long value;
    std::cout << prompt;
    std::cin >> value;
    while (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Try again: ";
        std::cin >> value;
    }
    return value;
}

double Read_double(const std::string &prompt) {
    double value;
    std::cout << prompt;
    std::cin >> value;
    while (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Try again: ";
        std::cin >> value;
    }
    return value;
}

long square_long(long x) { return x * x; }
bool greater_than_five_long(long x) { return x > 5; }
long sum_long(long acc, long x) { return acc + x; }

double square_double(double x) { return x * x; }
bool greater_than_five_double(double x) { return x > 5.0; }
double sum_double(double acc, double x) { return acc + x; }

Complex square_complex(Complex x) { return x * x; }
bool greater_than_five_complex(Complex x) {
    return (x.Get_real() * x.Get_real() + x.Get_imaginary() * x.Get_imaginary()) > 25.0;
}
Complex sum_complex(Complex acc, Complex x) { return acc + x; }

template <typename T> T Read_one();
template<> long Read_one<long>() { return Read_long("Value: "); }
template<> double Read_one<double>() { return Read_double("Value: "); }
template<> Complex Read_one<Complex>() { return Complex::Read(); }
template<> String Read_one<String>() { return String::Read(); }
template<> Student Read_one<Student>() { return Student::Read(); }
template<> Teacher Read_one<Teacher>() { return Teacher::Read(); }

template <typename T>
void Print_sequence(const Sequence<T> &seq, const std::string &name) {
    std::cout << name << " (length " << seq.Get_length() << "): [";
    for (long element_index = 0; element_index < seq.Get_length(); element_index ++) {
        if (element_index != 0) { std::cout << ", "; }
        std::cout << seq.Get(element_index);
    }
    std::cout << "]" << std::endl;
}

template <
    typename T,
    T (*MapFunc)(T),
    bool (*WhereFunc)(T),
    T (*ReduceFunc)(T, T)
>
void Deque_menu_full(T init_value) {
    SegmentedDequeSequence<T> *deq = new SegmentedDequeSequence<T>();
    int choice = 0;
    long max_choice = 19;

    while (choice != max_choice) {
        std::cout << "\n--- Segmented Deque ---\n";
        std::cout << "1. Append\n";
        std::cout << "2. Prepend\n";
        std::cout << "3. Insert at index\n";
        std::cout << "4. Get first\n";
        std::cout << "5. Get last\n";
        std::cout << "6. Get at index\n";
        std::cout << "7. Get length\n";
        std::cout << "8. Get subsequence\n";
        std::cout << "9. Print\n";
        std::cout << "10. Slice\n";
        std::cout << "11. Map\n";
        std::cout << "12. Where\n";
        std::cout << "13. Reduce\n";
        std::cout << "14. Try_get_first\n";
        std::cout << "15. Try_get_last\n";
        std::cout << "16. Zip\n";
        std::cout << "17. Flat_map\n";
        std::cout << "18. Sort\n";
        std::cout << "19. Exit\n";
        choice = Read_long("Your choice: ");

        if (choice == 1) {
            T value = Read_one<T>();
            deq -> Append(value);
            Print_sequence(*deq, "Deque");
        }
        else if (choice == 2) {
            T value = Read_one<T>();
            deq -> Prepend(value);
            Print_sequence(*deq, "Deque");
        }
        else if (choice == 3) {
            long index = Read_long("Index: ");
            T value = Read_one<T>();
            try {
                deq -> Insert_at(value, index);
                Print_sequence(*deq, "After insert");
            }
            catch (const Errors &err) { std::cout << "Error: " << err.Message() << std::endl; }
        }
        else if (choice == 4) {
            try { std::cout << "First: " << deq -> Get_first() << std::endl; }
            catch (const Errors &err) { std::cout << "Error: " << err.Message() << std::endl; }
        }
        else if (choice == 5) {
            try { std::cout << "Last: " << deq -> Get_last() << std::endl; }
            catch (const Errors &err) { std::cout << "Error: " << err.Message() << std::endl; }
        }
        else if (choice == 6) {
            long index = Read_long("Index: ");
            try { std::cout << "Element: " << deq -> Get(index) << std::endl; }
            catch (const Errors &err) { std::cout << "Error: " << err.Message() << std::endl; }
        }
        else if (choice == 7) {
            std::cout << "Length: " << deq -> Get_length() << std::endl;
        }
        else if (choice == 8) {
            long start = Read_long("Start: ");
            long end = Read_long("End: ");
            try {
                Sequence<T> *sub = deq -> Get_subsequence(start, end);
                Print_sequence(*sub, "Subsequence");
                delete sub;
            }
            catch (const Errors &err) { std::cout << "Error: " << err.Message() << std::endl; }
        }
        else if (choice == 9) {
            Print_sequence(*deq, "Deque");
        }
        else if (choice == 10) {
            long start = Read_long("Start: ");
            long count = Read_long("Count: ");
            long insert_count = Read_long("Insert count (0 for none): ");
            SegmentedDequeSequence<T> *insert_seq = nullptr;
            if (insert_count > 0) {
                insert_seq = new SegmentedDequeSequence<T>();
                for (long counter = 0; counter < insert_count; counter ++) {
                    std::cout << "Insert element " << counter << ": ";
                    insert_seq -> Append(Read_one<T>());
                }
            }
            Sequence<T> *result = deq -> Slice(start, count, insert_seq);
            Print_sequence(*result, "After slice");
            delete result;
            if (insert_seq != nullptr) { delete insert_seq; }
        }
        else if (choice == 11) {
            Sequence<T> *mapped = deq -> Map(MapFunc);
            Print_sequence(*mapped, "Mapped");
            delete mapped;
        }
        else if (choice == 12) {
            Sequence<T> *filtered = deq -> Where(WhereFunc);
            Print_sequence(*filtered, "Filtered");
            delete filtered;
        }
        else if (choice == 13) {
            T sum = deq -> Reduce(ReduceFunc, init_value);
            std::cout << "Sum: " << sum << std::endl;
        }
        else if (choice == 14) {
            Option<T> opt = deq -> Try_get_first(WhereFunc);
            if (opt.Is_some()) { std::cout << "Found: " << opt.Get() << std::endl; }
            else { std::cout << "Not found." << std::endl; }
        }
        else if (choice == 15) {
            Option<T> opt = deq -> Try_get_last(WhereFunc);
            if (opt.Is_some()) { std::cout << "Found: " << opt.Get() << std::endl; }
            else { std::cout << "Not found." << std::endl; }
        }
        else if (choice == 16) {
            std::cout << "Create another deque to zip:\n";
            SegmentedDequeSequence<T> *other = new SegmentedDequeSequence<T>();
            long count = Read_long("How many elements? ");
            for (long counter = 0; counter < count; counter ++) {
                other -> Append(Read_one<T>());
            }
            Sequence<T> *result = deq -> Zip(other);
            Print_sequence(*result, "Zipped");
            delete result;
            delete other;
        }
        else if (choice == 17) {
            Sequence<T> *result = deq -> Flat_map(
                [](T x) -> Sequence<T>* {
                    SegmentedDequeSequence<T> *s = new SegmentedDequeSequence<T>();
                    s -> Append(x);
                    s -> Append(x);
                    return s;
                }
            );
            Print_sequence(*result, "Flat_mapped");
            delete result;
        }
        else if (choice == 18) {
            SegmentedDequeSequence<T> *sorted = deq -> Sort();
            Print_sequence(*sorted, "Sorted");
            delete sorted;
        }
        else if (choice == 19) {
            std::cout << "Exiting.\n";
        }
        else {
            std::cout << "Invalid choice.\n";
        }
    }
    delete deq;
}

template <typename T>
void Deque_menu_basic() {
    SegmentedDequeSequence<T> *deq = new SegmentedDequeSequence<T>();
    int choice = 0;

    while (choice != 10) {
        std::cout << "\n--- Segmented Deque ---\n";
        std::cout << "1. Append\n";
        std::cout << "2. Prepend\n";
        std::cout << "3. Insert at index\n";
        std::cout << "4. Get first\n";
        std::cout << "5. Get last\n";
        std::cout << "6. Get at index\n";
        std::cout << "7. Get length\n";
        std::cout << "8. Get subsequence\n";
        std::cout << "9. Print\n";
        std::cout << "10. Exit\n";
        choice = Read_long("Your choice: ");

        if (choice == 1) {
            T value = Read_one<T>();
            deq -> Append(value);
            Print_sequence(*deq, "Deque");
        }
        else if (choice == 2) {
            T value = Read_one<T>();
            deq -> Prepend(value);
            Print_sequence(*deq, "Deque");
        }
        else if (choice == 3) {
            long index = Read_long("Index: ");
            T value = Read_one<T>();
            try {
                deq -> Insert_at(value, index);
                Print_sequence(*deq, "After insert");
            }
            catch (const Errors &err) { std::cout << "Error: " << err.Message() << std::endl; }
        }
        else if (choice == 4) {
            try { std::cout << "First: " << deq -> Get_first() << std::endl; }
            catch (const Errors &err) { std::cout << "Error: " << err.Message() << std::endl; }
        }
        else if (choice == 5) {
            try { std::cout << "Last: " << deq -> Get_last() << std::endl; }
            catch (const Errors &err) { std::cout << "Error: " << err.Message() << std::endl; }
        }
        else if (choice == 6) {
            long index = Read_long("Index: ");
            try { std::cout << "Element: " << deq -> Get(index) << std::endl; }
            catch (const Errors &err) { std::cout << "Error: " << err.Message() << std::endl; }
        }
        else if (choice == 7) {
            std::cout << "Length: " << deq -> Get_length() << std::endl;
        }
        else if (choice == 8) {
            long start = Read_long("Start: ");
            long end = Read_long("End: ");
            try {
                Sequence<T> *sub = deq -> Get_subsequence(start, end);
                Print_sequence(*sub, "Subsequence");
                delete sub;
            }
            catch (const Errors &err) { std::cout << "Error: " << err.Message() << std::endl; }
        }
        else if (choice == 9) {
            Print_sequence(*deq, "Deque");
        }
        else if (choice == 10) {
            std::cout << "Exiting.\n";
        }
        else {
            std::cout << "Invalid choice.\n";
        }
    }
    delete deq;
}

int main() {
    std::cout << "=== Segmented Deque Tester ===\n";
    int type = 0;
    while (type != 8) {
        std::cout << "\nSelect option:\n";
        std::cout << "1. Long\n";
        std::cout << "2. Double\n";
        std::cout << "3. Complex\n";
        std::cout << "4. String\n";
        std::cout << "5. Student\n";
        std::cout << "6. Teacher\n";
        std::cout << "7. Run tests\n";
        std::cout << "8. Exit\n";
        type = Read_long("Choice: ");
        switch (type) {
            case 1: Deque_menu_full<long, square_long, greater_than_five_long, sum_long>(0); break;
            case 2: Deque_menu_full<double, square_double, greater_than_five_double, sum_double>(0.0); break;
            case 3: Deque_menu_full<Complex, square_complex, greater_than_five_complex, sum_complex>(Complex(0, 0)); break;
            case 4: Deque_menu_basic<String>(); break;
            case 5: Deque_menu_basic<Student>(); break;
            case 6: Deque_menu_basic<Teacher>(); break;
            case 7: Run_tests(); break;
            case 8: std::cout << "Goodbye!\n"; break;
            default: std::cout << "Invalid choice.\n";
        }
    }
    return 0;
}