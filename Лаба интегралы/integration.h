#ifndef INTEGRATION_H
#define INTEGRATION_H

#include <cstdint>

// Подынтегральные функции
double f_exp(double x);      // e^(0.1x)/x
double f_sin(double x);      // sin(0.4x)·x^0.23
double f_cubic(double x);    // 1/(1+x³)

// Методы численного интегрирования для фиксированного n
double left_rectangles(double (*func)(double), double a, double b, int32_t n);
double right_rectangles(double (*func)(double), double a, double b, int32_t n);
double middle_rectangles(double (*func)(double), double a, double b, int32_t n);
double trapezoidal(double (*func)(double), double a, double b, int32_t n);
double simpson(double (*func)(double), double a, double b, int32_t n);

#endif