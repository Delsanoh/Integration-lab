#include <iostream>
#include <cmath>
#include "integration.h"

// 1. f_exp(x) = e^(0.1x)/x
double f_exp(double x) {
    return std::exp(0.1 * x) / x;
}

// 2. f_sin(x) = sin(0.4x)·x^0.23
double f_sin(double x) {
    return std::sin(0.4 * x) * std::pow(x, 0.23);
}

// 3. f_cubic(x) = 1/(1+x³)
double f_cubic(double x) {
    return 1.0 / (1.0 + x * x * x);
}

// Методы интегрирования для фиксированного n
double left_rectangles(double (*func)(double), double a, double b, int32_t n) {
    double h = (b - a) / n;
    double sum = 0.0;

    for (int32_t i = 0; i < n; i++) {
        double x = a + i * h;
        sum += func(x);
    }

    return sum * h;
}

double right_rectangles(double (*func)(double), double a, double b, int32_t n) {
    double h = (b - a) / n;
    double sum = 0.0;

    for (int32_t i = 1; i <= n; i++) {
        double x = a + i * h;
        sum += func(x);
    }

    return sum * h;
}

double middle_rectangles(double (*func)(double), double a, double b, int32_t n) {
    double h = (b - a) / n;
    double sum = 0.0;

    for (int32_t i = 0; i < n; i++) {
        double x = a + i * h + h / 2.0;
        sum += func(x);
    }

    return sum * h;
}

double trapezoidal(double (*func)(double), double a, double b, int32_t n) {
    double h = (b - a) / n;
    double sum = (func(a) + func(b)) / 2.0;

    for (int32_t i = 1; i < n; i++) {
        double x = a + i * h;
        sum += func(x);
    }

    return sum * h;
}

double simpson(double (*func)(double), double a, double b, int32_t n) {
    if (n % 2 != 0) n++; // Делаем n четным для метода Симпсона

    double h = (b - a) / n;
    double sum = func(a) + func(b);

    // Нечетные точки (коэффициент 4)
    for (int32_t i = 1; i < n; i += 2) {
        double x = a + i * h;
        sum += 4.0 * func(x);
    }

    // Четные точки (коэффициент 2)
    for (int32_t i = 2; i < n; i += 2) {
        double x = a + i * h;
        sum += 2.0 * func(x);
    }

    return sum * h / 3.0;
}
