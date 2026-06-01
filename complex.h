#ifndef Complex_H
#define Complex_H

#include <iostream>

class Complex {
private:
    double real;
    double imaginary;

public:
    Complex() : real(0), imaginary(0) {}

    Complex(double real_part, double imaginary_part) : real(real_part), imaginary(imaginary_part) {}

    double Get_real() const { return real; }

    double Get_imaginary() const { return imaginary; }

    void Set_real(double value) { real = value; }

    void Set_imaginary(double value) { imaginary = value; }

    bool operator==(const Complex &other) const {
        return (real == other.real) && (imaginary == other.imaginary);
    }

    operator double() const {
        return (real * real) + (imaginary * imaginary);
    }

    Complex& operator=(const Complex &other) {
        real = other.real;
        imaginary = other.imaginary;
        return *this;
    }

    Complex operator+(const Complex &other) const {
        return Complex(real + other.real, imaginary + other.imaginary);
    }

    Complex operator-(const Complex &other) const {
        return Complex(real - other.real, imaginary - other.imaginary);
    }

    Complex operator*(const Complex &other) const {
        return Complex(real * other.real - imaginary * other.imaginary,
                       real * other.imaginary + imaginary * other.real);
    }

    Complex& operator+=(const Complex &other) {
        real += other.real;
        imaginary += other.imaginary;
        return *this;
    }

    Complex& operator-=(const Complex &other) {
        real -= other.real;
        imaginary -= other.imaginary;
        return *this;
    }

    Complex& operator*=(const Complex &other) {
        double new_real = real * other.real - imaginary * other.imaginary;
        double new_imag = real * other.imaginary + imaginary * other.real;
        real = new_real;
        imaginary = new_imag;
        return *this;
    }

    static Complex Read();
};

std::ostream& operator<<(std::ostream &os, const Complex &value);

#endif //Complex_H