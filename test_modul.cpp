#include <iostream>
#include "lab_2/MutableArraySequence.h"
#include "SegmentedDequeSequence.h"
#include "Complex.h"
#include "String.h"
#include "Student.h"
#include "Teacher.h"
#include "lab_2/Errors.h"

static int tests_passed = 0;
static int tests_failed = 0;

static void Register_test(void (*test_func)(), const std::string &test_name) {
    try {
        test_func();
        tests_passed ++;
        std::cout << "[PASS] " << test_name << std::endl;
    }
    catch (const Errors &err) {
        tests_failed ++;
        std::cout << "[FAIL] " << test_name << " " << err.Message() << std::endl;
    }
}

#define ASSERT_EQ(x, y) \
    if ((x) != (y)) { throw Errors("ASSERT_EQ failed"); }

#define ASSERT_THROWS(expr, exc_type) \
    { \
        bool caught = false; \
        try { expr; } \
        catch (const exc_type&) { caught = true; } \
        catch (const Errors&) {} \
        if (caught == false) { throw Errors("ASSERT_THROWS failed"); } \
    }

static long square_long(long x) { return x * x; }
static bool is_even_long(long x) { return x % 2 == 0; }
static long sum_long(long acc, long x) { return acc + x; }
static Sequence<long>* duplicate_long(long x) {
    SegmentedDequeSequence<long> *seq = new SegmentedDequeSequence<long>();
    seq -> Append(x);
    seq -> Append(x);
    return seq;
}

// ==================== Complex ====================

static void Test_Complex_default_constructor() {
    Complex value;
    ASSERT_EQ(value.Get_real(), 0.0);
    ASSERT_EQ(value.Get_imaginary(), 0.0);
}

static void Test_Complex_constructor() {
    Complex value(3.0, 4.0);
    ASSERT_EQ(value.Get_real(), 3.0);
    ASSERT_EQ(value.Get_imaginary(), 4.0);
}

static void Test_Complex_get_set() {
    Complex value;
    value.Set_real(5.0);
    value.Set_imaginary(6.0);
    ASSERT_EQ(value.Get_real(), 5.0);
    ASSERT_EQ(value.Get_imaginary(), 6.0);
}

static void Test_Complex_equality() {
    Complex first(1.0, 2.0);
    Complex second(1.0, 2.0);
    Complex third(1.0, 3.0);
    ASSERT_EQ(first == second, true);
    ASSERT_EQ(first == third, false);
}

static void Test_Complex_addition() {
    Complex first(1.0, 2.0);
    Complex second(3.0, 4.0);
    Complex result = first + second;
    ASSERT_EQ(result.Get_real(), 4.0);
    ASSERT_EQ(result.Get_imaginary(), 6.0);
}

static void Test_Complex_subtraction() {
    Complex first(3.0, 4.0);
    Complex second(1.0, 2.0);
    Complex result = first - second;
    ASSERT_EQ(result.Get_real(), 2.0);
    ASSERT_EQ(result.Get_imaginary(), 2.0);
}

static void Test_Complex_multiplication() {
    Complex first(1.0, 2.0);
    Complex second(3.0, 4.0);
    Complex result = first * second;
    ASSERT_EQ(result.Get_real(), -5.0);
    ASSERT_EQ(result.Get_imaginary(), 10.0);
}

static void Test_Complex_add_assign() {
    Complex value(1.0, 2.0);
    value += Complex(3.0, 4.0);
    ASSERT_EQ(value.Get_real(), 4.0);
    ASSERT_EQ(value.Get_imaginary(), 6.0);
}

static void Test_Complex_sub_assign() {
    Complex value(3.0, 4.0);
    value -= Complex(1.0, 2.0);
    ASSERT_EQ(value.Get_real(), 2.0);
    ASSERT_EQ(value.Get_imaginary(), 2.0);
}

static void Test_Complex_mul_assign() {
    Complex value(1.0, 2.0);
    value *= Complex(3.0, 4.0);
    ASSERT_EQ(value.Get_real(), -5.0);
    ASSERT_EQ(value.Get_imaginary(), 10.0);
}

static void Test_Complex_double_conversion() {
    Complex value(3.0, 4.0);
    double mod = value;
    ASSERT_EQ(mod, 25.0);
}

static void Test_Complex_assignment() {
    Complex first(1.0, 2.0);
    Complex second;
    second = first;
    ASSERT_EQ(second.Get_real(), 1.0);
    ASSERT_EQ(second.Get_imaginary(), 2.0);
}

// ==================== String ====================

static void Test_String_default_constructor() {
    String str;
    ASSERT_EQ(str.Get_length(), 0);
}

static void Test_String_cstr_constructor() {
    String str("hello");
    ASSERT_EQ(str.Get_length(), 5);
    ASSERT_EQ(str == String("hello"), true);
}

static void Test_String_copy_constructor() {
    String first("hello");
    String second(first);
    ASSERT_EQ(second.Get_length(), 5);
    ASSERT_EQ(first == second, true);
}

static void Test_String_assignment() {
    String first("hello");
    String second;
    second = first;
    ASSERT_EQ(second == first, true);
}

static void Test_String_equality() {
    String first("hello");
    String second("hello");
    String third("world");
    ASSERT_EQ(first == second, true);
    ASSERT_EQ(first == third, false);
}

static void Test_String_not_equal() {
    String first("hello");
    String second("world");
    ASSERT_EQ(first != second, true);
}

static void Test_String_less_than() {
    String first("abc");
    String second("def");
    ASSERT_EQ(first < second, true);
    ASSERT_EQ(second < first, false);
}

static void Test_String_concatenation() {
    String first("hello");
    String second("world");
    String result = first + second;
    ASSERT_EQ(result == String("helloworld"), true);
    ASSERT_EQ(result.Get_length(), 10);
}

static void Test_String_nullptr_constructor() {
    String str(nullptr);
    ASSERT_EQ(str.Get_length(), 0);
}

// ==================== Student ====================

static void Test_Student_default_constructor() {
    Student value;
    ASSERT_EQ(value.Get_id(), 0);
    ASSERT_EQ(value.Get_birth_year(), 0);
}

static void Test_Student_constructor() {
    Student value(String("Ivan"), String("Ivanovich"), String("Ivanov"), 123, 2000);
    ASSERT_EQ(value.Get_id(), 123);
    ASSERT_EQ(value.Get_birth_year(), 2000);
}

static void Test_Student_get_full_name() {
    Student value(String("Ivan"), String("Ivanovich"), String("Ivanov"), 123, 2000);
    ASSERT_EQ(value.Get_full_name() == String("Ivanov Ivan Ivanovich"), true);
}

static void Test_Student_equality() {
    Student first(String("A"), String("B"), String("C"), 100, 2000);
    Student second(String("X"), String("Y"), String("Z"), 100, 2005);
    Student third(String("A"), String("B"), String("C"), 200, 2000);
    ASSERT_EQ(first == second, true);
    ASSERT_EQ(first == third, false);
}

static void Test_Student_not_equal() {
    Student first(String("A"), String("B"), String("C"), 100, 2000);
    Student second(String("A"), String("B"), String("C"), 200, 2000);
    ASSERT_EQ(first != second, true);
}

// ==================== Teacher ====================

static void Test_Teacher_default_constructor() {
    Teacher value;
    ASSERT_EQ(value.Get_id(), 0);
}

static void Test_Teacher_constructor() {
    Teacher value(String("Petr"), String("Petrovich"), String("Petrov"), 456, String("Math"));
    ASSERT_EQ(value.Get_id(), 456);
    ASSERT_EQ(value.Get_department() == String("Math"), true);
}

static void Test_Teacher_get_full_name() {
    Teacher value(String("Petr"), String("Petrovich"), String("Petrov"), 456, String("Math"));
    ASSERT_EQ(value.Get_full_name() == String("Petrov Petr Petrovich"), true);
}

static void Test_Teacher_equality() {
    Teacher first(String("A"), String("B"), String("C"), 100, String("D1"));
    Teacher second(String("X"), String("Y"), String("Z"), 100, String("D2"));
    Teacher third(String("A"), String("B"), String("C"), 200, String("D1"));
    ASSERT_EQ(first == second, true);
    ASSERT_EQ(first == third, false);
}

static void Test_Teacher_not_equal() {
    Teacher first(String("A"), String("B"), String("C"), 100, String("D1"));
    Teacher second(String("A"), String("B"), String("C"), 200, String("D1"));
    ASSERT_EQ(first != second, true);
}

// ==================== SegmentedDequeSequence ====================

static void Test_Deque_default_constructor() {
    SegmentedDequeSequence<long> deq;
    ASSERT_EQ(deq.Get_length(), 0);
}

static void Test_Deque_append() {
    SegmentedDequeSequence<long> deq;
    deq.Append(10);
    deq.Append(20);
    deq.Append(30);
    ASSERT_EQ(deq.Get_length(), 3);
    ASSERT_EQ(deq.Get_first(), 10);
    ASSERT_EQ(deq.Get_last(), 30);
}

static void Test_Deque_prepend() {
    SegmentedDequeSequence<long> deq;
    deq.Prepend(10);
    deq.Prepend(20);
    deq.Prepend(30);
    ASSERT_EQ(deq.Get_length(), 3);
    ASSERT_EQ(deq.Get_first(), 30);
    ASSERT_EQ(deq.Get_last(), 10);
}

static void Test_Deque_append_prepend_mixed() {
    SegmentedDequeSequence<long> deq;
    deq.Append(20);
    deq.Prepend(10);
    deq.Append(30);
    deq.Prepend(5);
    ASSERT_EQ(deq.Get_length(), 4);
    ASSERT_EQ(deq.Get(0), 5);
    ASSERT_EQ(deq.Get(1), 10);
    ASSERT_EQ(deq.Get(2), 20);
    ASSERT_EQ(deq.Get(3), 30);
}

static void Test_Deque_get_first_empty() {
    SegmentedDequeSequence<long> deq;
    ASSERT_THROWS(deq.Get_first(), EmptyCollection);
}

static void Test_Deque_get_last_empty() {
    SegmentedDequeSequence<long> deq;
    ASSERT_THROWS(deq.Get_last(), EmptyCollection);
}

static void Test_Deque_get_out_of_range() {
    SegmentedDequeSequence<long> deq;
    deq.Append(10);
    deq.Append(20);
    deq.Append(30);
    ASSERT_THROWS(deq.Get(3), IndexOutOfRange);
    ASSERT_THROWS(deq.Get(-1), IndexOutOfRange);
}

static void Test_Deque_insert_at_beginning() {
    SegmentedDequeSequence<long> deq;
    deq.Append(20);
    deq.Append(30);
    deq.Append(40);
    deq.Insert_at(10, 0);
    ASSERT_EQ(deq.Get_length(), 4);
    ASSERT_EQ(deq.Get(0), 10);
    ASSERT_EQ(deq.Get(1), 20);
    ASSERT_EQ(deq.Get(2), 30);
    ASSERT_EQ(deq.Get(3), 40);
}

static void Test_Deque_insert_at_end() {
    SegmentedDequeSequence<long> deq;
    deq.Append(10);
    deq.Append(20);
    deq.Append(30);
    deq.Insert_at(40, 3);
    ASSERT_EQ(deq.Get_length(), 4);
    ASSERT_EQ(deq.Get(3), 40);
}

static void Test_Deque_insert_at_middle() {
    SegmentedDequeSequence<long> deq;
    deq.Append(10);
    deq.Append(30);
    deq.Append(40);
    deq.Insert_at(20, 1);
    ASSERT_EQ(deq.Get_length(), 4);
    ASSERT_EQ(deq.Get(0), 10);
    ASSERT_EQ(deq.Get(1), 20);
    ASSERT_EQ(deq.Get(2), 30);
    ASSERT_EQ(deq.Get(3), 40);
}

static void Test_Deque_insert_at_out_of_range() {
    SegmentedDequeSequence<long> deq;
    deq.Append(10);
    deq.Append(20);
    deq.Append(30);
    ASSERT_THROWS(deq.Insert_at(99, 5), IndexOutOfRange);
    ASSERT_THROWS(deq.Insert_at(99, -1), IndexOutOfRange);
}

static void Test_Deque_get_subsequence() {
    SegmentedDequeSequence<long> deq;
    deq.Append(10);
    deq.Append(20);
    deq.Append(30);
    deq.Append(40);
    deq.Append(50);
    Sequence<long> *sub = deq.Get_subsequence(1, 3);
    ASSERT_EQ(sub -> Get_length(), 3);
    ASSERT_EQ(sub -> Get(0), 20);
    ASSERT_EQ(sub -> Get(1), 30);
    ASSERT_EQ(sub -> Get(2), 40);
    delete sub;
}

static void Test_Deque_get_subsequence_bad_indices() {
    SegmentedDequeSequence<long> deq;
    deq.Append(10);
    deq.Append(20);
    deq.Append(30);
    ASSERT_THROWS(deq.Get_subsequence(-1, 1), IndexOutOfRange);
    ASSERT_THROWS(deq.Get_subsequence(1, 0), IndexesTranslated);
}

static void Test_Deque_concat() {
    SegmentedDequeSequence<long> deq1;
    deq1.Append(1);
    deq1.Append(2);
    deq1.Append(3);
    SegmentedDequeSequence<long> deq2;
    deq2.Append(4);
    deq2.Append(5);
    deq2.Append(6);
    deq1.Concat(&deq2);
    ASSERT_EQ(deq1.Get_length(), 6);
    ASSERT_EQ(deq1.Get(0), 1);
    ASSERT_EQ(deq1.Get(5), 6);
}

static void Test_Deque_concat_nullptr() {
    SegmentedDequeSequence<long> deq;
    ASSERT_THROWS(deq.Concat(nullptr), NullPointerError);
}

static void Test_Deque_map() {
    SegmentedDequeSequence<long> deq;
    deq.Append(1);
    deq.Append(2);
    deq.Append(3);
    Sequence<long> *mapped = deq.Map(square_long);
    ASSERT_EQ(mapped -> Get_length(), 3);
    ASSERT_EQ(mapped -> Get(0), 1);
    ASSERT_EQ(mapped -> Get(1), 4);
    ASSERT_EQ(mapped -> Get(2), 9);
    delete mapped;
}

static void Test_Deque_map_nullptr() {
    SegmentedDequeSequence<long> deq;
    ASSERT_THROWS(deq.Map(nullptr), NullPointerError);
}

static void Test_Deque_where() {
    SegmentedDequeSequence<long> deq;
    deq.Append(1);
    deq.Append(2);
    deq.Append(3);
    deq.Append(4);
    deq.Append(5);
    Sequence<long> *filtered = deq.Where(is_even_long);
    ASSERT_EQ(filtered -> Get_length(), 2);
    ASSERT_EQ(filtered -> Get(0), 2);
    ASSERT_EQ(filtered -> Get(1), 4);
    delete filtered;
}

static void Test_Deque_where_nullptr() {
    SegmentedDequeSequence<long> deq;
    ASSERT_THROWS(deq.Where(nullptr), NullPointerError);
}

static void Test_Deque_reduce() {
    SegmentedDequeSequence<long> deq;
    deq.Append(1);
    deq.Append(2);
    deq.Append(3);
    long sum = deq.Reduce(sum_long, 0);
    ASSERT_EQ(sum, 6);
}

static void Test_Deque_reduce_nullptr() {
    SegmentedDequeSequence<long> deq;
    ASSERT_THROWS(deq.Reduce(nullptr, 0), NullPointerError);
}

static void Test_Deque_try_get_first() {
    SegmentedDequeSequence<long> deq;
    deq.Append(1);
    deq.Append(2);
    deq.Append(3);
    Option<long> opt = deq.Try_get_first(is_even_long);
    ASSERT_EQ(opt.Is_some(), true);
    ASSERT_EQ(opt.Get(), 2);
}

static void Test_Deque_try_get_first_not_found() {
    SegmentedDequeSequence<long> deq;
    deq.Append(1);
    deq.Append(3);
    deq.Append(5);
    Option<long> opt = deq.Try_get_first(is_even_long);
    ASSERT_EQ(opt.Is_none(), true);
}

static void Test_Deque_try_get_last() {
    SegmentedDequeSequence<long> deq;
    deq.Append(1);
    deq.Append(2);
    deq.Append(3);
    deq.Append(4);
    Option<long> opt = deq.Try_get_last(is_even_long);
    ASSERT_EQ(opt.Is_some(), true);
    ASSERT_EQ(opt.Get(), 4);
}

static void Test_Deque_try_get_last_not_found() {
    SegmentedDequeSequence<long> deq;
    deq.Append(1);
    deq.Append(3);
    deq.Append(5);
    Option<long> opt = deq.Try_get_last(is_even_long);
    ASSERT_EQ(opt.Is_none(), true);
}

static void Test_Deque_slice() {
    SegmentedDequeSequence<long> deq;
    deq.Append(10);
    deq.Append(20);
    deq.Append(30);
    deq.Append(40);
    deq.Append(50);
    Sequence<long> *result = deq.Slice(1, 2);
    ASSERT_EQ(result -> Get_length(), 3);
    ASSERT_EQ(result -> Get(0), 10);
    ASSERT_EQ(result -> Get(1), 40);
    ASSERT_EQ(result -> Get(2), 50);
    delete result;
}

static void Test_Deque_slice_with_insert() {
    SegmentedDequeSequence<long> deq;
    deq.Append(10);
    deq.Append(20);
    deq.Append(30);
    deq.Append(40);
    SegmentedDequeSequence<long> insert_seq;
    insert_seq.Append(60);
    insert_seq.Append(70);
    insert_seq.Append(80);
    Sequence<long> *result = deq.Slice(1, 2, &insert_seq);
    ASSERT_EQ(result -> Get_length(), 5);
    ASSERT_EQ(result -> Get(0), 10);
    ASSERT_EQ(result -> Get(1), 60);
    ASSERT_EQ(result -> Get(2), 70);
    ASSERT_EQ(result -> Get(3), 80);
    ASSERT_EQ(result -> Get(4), 40);
    delete result;
}

static void Test_Deque_zip() {
    SegmentedDequeSequence<long> deq1;
    deq1.Append(1);
    deq1.Append(3);
    deq1.Append(5);
    SegmentedDequeSequence<long> deq2;
    deq2.Append(2);
    deq2.Append(4);
    deq2.Append(6);
    Sequence<long> *result = deq1.Zip(&deq2);
    ASSERT_EQ(result -> Get_length(), 6);
    ASSERT_EQ(result -> Get(0), 1);
    ASSERT_EQ(result -> Get(1), 2);
    ASSERT_EQ(result -> Get(2), 3);
    ASSERT_EQ(result -> Get(3), 4);
    ASSERT_EQ(result -> Get(4), 5);
    ASSERT_EQ(result -> Get(5), 6);
    delete result;
}

static void Test_Deque_flat_map() {
    SegmentedDequeSequence<long> deq;
    deq.Append(1);
    deq.Append(2);
    deq.Append(3);
    Sequence<long> *result = deq.Flat_map(duplicate_long);
    ASSERT_EQ(result -> Get_length(), 6);
    ASSERT_EQ(result -> Get(0), 1);
    ASSERT_EQ(result -> Get(1), 1);
    ASSERT_EQ(result -> Get(2), 2);
    ASSERT_EQ(result -> Get(3), 2);
    ASSERT_EQ(result -> Get(4), 3);
    ASSERT_EQ(result -> Get(5), 3);
    delete result;
}

static void Test_Deque_contains_subsequence() {
    SegmentedDequeSequence<long> deq;
    deq.Append(1);
    deq.Append(2);
    deq.Append(3);
    deq.Append(4);
    SegmentedDequeSequence<long> sub;
    sub.Append(2);
    sub.Append(3);
    ASSERT_EQ(deq.Contains_subsequence(sub), true);
}

static void Test_Deque_contains_subsequence_not_found() {
    SegmentedDequeSequence<long> deq;
    deq.Append(1);
    deq.Append(2);
    deq.Append(3);
    SegmentedDequeSequence<long> sub;
    sub.Append(2);
    sub.Append(4);
    ASSERT_EQ(deq.Contains_subsequence(sub), false);
}

static void Test_Deque_contains_subsequence_empty() {
    SegmentedDequeSequence<long> deq;
    deq.Append(1);
    deq.Append(2);
    deq.Append(3);
    SegmentedDequeSequence<long> sub;
    ASSERT_EQ(deq.Contains_subsequence(sub), true);
}

static void Test_Deque_sort() {
    SegmentedDequeSequence<long> deq;
    deq.Append(30);
    deq.Append(10);
    deq.Append(40);
    deq.Append(20);
    deq.Append(50);
    SegmentedDequeSequence<long> *sorted = deq.Sort();
    ASSERT_EQ(sorted -> Get_length(), 5);
    ASSERT_EQ(sorted -> Get(0), 10);
    ASSERT_EQ(sorted -> Get(1), 20);
    ASSERT_EQ(sorted -> Get(2), 30);
    ASSERT_EQ(sorted -> Get(3), 40);
    ASSERT_EQ(sorted -> Get(4), 50);
    ASSERT_EQ(deq.Get(0), 30);
    delete sorted;
}

static void Test_Deque_equality() {
    SegmentedDequeSequence<long> deq1;
    deq1.Append(1);
    deq1.Append(2);
    deq1.Append(3);
    SegmentedDequeSequence<long> deq2;
    deq2.Append(1);
    deq2.Append(2);
    deq2.Append(3);
    SegmentedDequeSequence<long> deq3;
    deq3.Append(1);
    deq3.Append(2);
    deq3.Append(4);
    ASSERT_EQ(deq1 == deq2, true);
    ASSERT_EQ(deq1 == deq3, false);
}

static void Test_Deque_clone() {
    SegmentedDequeSequence<long> deq;
    deq.Append(10);
    deq.Append(20);
    deq.Append(30);
    SegmentedDequeSequence<long> *clone = deq.Clone();
    ASSERT_EQ(clone -> Get_length(), 3);
    ASSERT_EQ(clone -> Get(0), 10);
    ASSERT_EQ(clone -> Get(1), 20);
    ASSERT_EQ(clone -> Get(2), 30);
    ASSERT_EQ(clone != &deq, true);
    delete clone;
}

static void Test_Deque_many_elements() {
    SegmentedDequeSequence<long> deq;
    for (long counter = 0; counter < 100; counter ++) {
        deq.Append(counter);
    }
    ASSERT_EQ(deq.Get_length(), 100);
    ASSERT_EQ(deq.Get(0), 0);
    ASSERT_EQ(deq.Get(99), 99);
}

static void Test_Deque_copy_constructor() {
    SegmentedDequeSequence<long> deq;
    deq.Append(10);
    deq.Append(20);
    deq.Append(30);
    SegmentedDequeSequence<long> copy(deq);
    ASSERT_EQ(copy.Get_length(), 3);
    ASSERT_EQ(copy.Get(0), 10);
    ASSERT_EQ(copy.Get(1), 20);
    ASSERT_EQ(copy.Get(2), 30);
}

// ==================== Run_tests ====================

void Run_tests() {
    Register_test(Test_Complex_default_constructor, "Complex_default_constructor");
    Register_test(Test_Complex_constructor, "Complex_constructor");
    Register_test(Test_Complex_get_set, "Complex_get_set");
    Register_test(Test_Complex_equality, "Complex_equality");
    Register_test(Test_Complex_addition, "Complex_addition");
    Register_test(Test_Complex_subtraction, "Complex_subtraction");
    Register_test(Test_Complex_multiplication, "Complex_multiplication");
    Register_test(Test_Complex_add_assign, "Complex_add_assign");
    Register_test(Test_Complex_sub_assign, "Complex_sub_assign");
    Register_test(Test_Complex_mul_assign, "Complex_mul_assign");
    Register_test(Test_Complex_double_conversion, "Complex_double_conversion");
    Register_test(Test_Complex_assignment, "Complex_assignment");

    Register_test(Test_String_default_constructor, "String_default_constructor");
    Register_test(Test_String_cstr_constructor, "String_cstr_constructor");
    Register_test(Test_String_copy_constructor, "String_copy_constructor");
    Register_test(Test_String_assignment, "String_assignment");
    Register_test(Test_String_equality, "String_equality");
    Register_test(Test_String_not_equal, "String_not_equal");
    Register_test(Test_String_less_than, "String_less_than");
    Register_test(Test_String_concatenation, "String_concatenation");
    Register_test(Test_String_nullptr_constructor, "String_nullptr_constructor");

    Register_test(Test_Student_default_constructor, "Student_default_constructor");
    Register_test(Test_Student_constructor, "Student_constructor");
    Register_test(Test_Student_get_full_name, "Student_get_full_name");
    Register_test(Test_Student_equality, "Student_equality");
    Register_test(Test_Student_not_equal, "Student_not_equal");

    Register_test(Test_Teacher_default_constructor, "Teacher_default_constructor");
    Register_test(Test_Teacher_constructor, "Teacher_constructor");
    Register_test(Test_Teacher_get_full_name, "Teacher_get_full_name");
    Register_test(Test_Teacher_equality, "Teacher_equality");
    Register_test(Test_Teacher_not_equal, "Teacher_not_equal");

    Register_test(Test_Deque_default_constructor, "Deque_default_constructor");
    Register_test(Test_Deque_append, "Deque_append");
    Register_test(Test_Deque_prepend, "Deque_prepend");
    Register_test(Test_Deque_append_prepend_mixed, "Deque_append_prepend_mixed");
    Register_test(Test_Deque_get_first_empty, "Deque_get_first_empty");
    Register_test(Test_Deque_get_last_empty, "Deque_get_last_empty");
    Register_test(Test_Deque_get_out_of_range, "Deque_get_out_of_range");
    Register_test(Test_Deque_insert_at_beginning, "Deque_insert_at_beginning");
    Register_test(Test_Deque_insert_at_end, "Deque_insert_at_end");
    Register_test(Test_Deque_insert_at_middle, "Deque_insert_at_middle");
    Register_test(Test_Deque_insert_at_out_of_range, "Deque_insert_at_out_of_range");
    Register_test(Test_Deque_get_subsequence, "Deque_get_subsequence");
    Register_test(Test_Deque_get_subsequence_bad_indices, "Deque_get_subsequence_bad_indices");
    Register_test(Test_Deque_concat, "Deque_concat");
    Register_test(Test_Deque_concat_nullptr, "Deque_concat_nullptr");
    Register_test(Test_Deque_map, "Deque_map");
    Register_test(Test_Deque_map_nullptr, "Deque_map_nullptr");
    Register_test(Test_Deque_where, "Deque_where");
    Register_test(Test_Deque_where_nullptr, "Deque_where_nullptr");
    Register_test(Test_Deque_reduce, "Deque_reduce");
    Register_test(Test_Deque_reduce_nullptr, "Deque_reduce_nullptr");
    Register_test(Test_Deque_try_get_first, "Deque_try_get_first");
    Register_test(Test_Deque_try_get_first_not_found, "Deque_try_get_first_not_found");
    Register_test(Test_Deque_try_get_last, "Deque_try_get_last");
    Register_test(Test_Deque_try_get_last_not_found, "Deque_try_get_last_not_found");
    Register_test(Test_Deque_slice, "Deque_slice");
    Register_test(Test_Deque_slice_with_insert, "Deque_slice_with_insert");
    Register_test(Test_Deque_zip, "Deque_zip");
    Register_test(Test_Deque_flat_map, "Deque_flat_map");
    Register_test(Test_Deque_contains_subsequence, "Deque_contains_subsequence");
    Register_test(Test_Deque_contains_subsequence_not_found, "Deque_contains_subsequence_not_found");
    Register_test(Test_Deque_contains_subsequence_empty, "Deque_contains_subsequence_empty");
    Register_test(Test_Deque_sort, "Deque_sort");
    Register_test(Test_Deque_equality, "Deque_equality");
    Register_test(Test_Deque_clone, "Deque_clone");
    Register_test(Test_Deque_many_elements, "Deque_many_elements");
    Register_test(Test_Deque_copy_constructor, "Deque_copy_constructor");

    std::cout << "\n=== Test Results ===" << std::endl;
    std::cout << "Passed: " << tests_passed << std::endl;
    std::cout << "Failed: " << tests_failed << std::endl;

    if (tests_failed == 0) {
        std::cout << "All tests passed!" << std::endl;
    }
}