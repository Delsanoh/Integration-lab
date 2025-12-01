#include <iostream>
#include <cmath>
#include "integration.h"
//f(x) = sin(0.4 * x) / (1 + x)

double f(double x) {
    return std::sin(0.4 * x) / (1.0 + x);
}

double left_rectangles(double (*func)(double), double a, double b, double eps, int32_t& n_final) {
    int32_t n = 4;
    double s1, s2 = 0.0;

    do {
        s1 = s2;
        n *= 2;
        double h = (b - a) / n;
        s2 = 0.0;

        for (int32_t i = 0; i < n; i++) {
            double x = a + i * h;
            s2 += func(x);
        }
        s2 *= h;

    } while (std::fabs(s1 - s2) > eps);

    n_final = n;
    return s2;
}

double right_rectangles(double (*func)(double), double a, double b, double eps, int32_t& n_final) {
    int32_t n = 4;
    double s1, s2 = 0.0;

    do {
        s1 = s2;
        n *= 2;
        double h = (b - a) / n;
        s2 = 0.0;

        for (int32_t i = 1; i <= n; i++) {
            double x = a + i * h;
            s2 += func(x);
        }
        s2 *= h;

    } while (std::fabs(s1 - s2) > eps);

    n_final = n;
    return s2;
}

double middle_rectangles(double (*func)(double), double a, double b, double eps, int32_t& n_final) {
    int32_t n = 4;
    double s1, s2 = 0.0;

    do {
        s1 = s2;
        n *= 2;
        double h = (b - a) / n;
        s2 = 0.0;

        for (int32_t i = 0; i < n; i++) {
            double x = a + i * h + h / 2.0;
            s2 += func(x);
        }
        s2 *= h;

    } while (std::fabs(s1 - s2) > eps);

    n_final = n;
    return s2;
}

double trapezoidal(double (*func)(double), double a, double b, double eps, int32_t& n_final) {
    int32_t n = 4;
    double s1, s2 = 0.0;

    do {
        s1 = s2;
        n *= 2;
        double h = (b - a) / n;
        s2 = (func(a) + func(b)) / 2.0;

        for (int32_t i = 1; i < n; i++) {
            double x = a + i * h;
            s2 += func(x);
        }
        s2 *= h;

    } while (std::fabs(s1 - s2) > eps);

    n_final = n;
    return s2;
}

double simpson(double (*func)(double), double a, double b, double eps, int32_t& n_final) {
    int32_t n = 4;
    double s1, s2 = 0.0;

    do {
        s1 = s2;
        n *= 2;
        double h = (b - a) / n;
        s2 = func(a) + func(b);

        for (int32_t i = 1; i < n; i += 2) {
            double x = a + i * h;
            s2 += 4.0 * func(x);
        }

        for (int32_t i = 2; i < n; i += 2) {
            double x = a + i * h;
            s2 += 2.0 * func(x);
        }

        s2 *= h / 3.0;

    } while (std::fabs(s1 - s2) > eps);

    n_final = n;
    return s2;
}