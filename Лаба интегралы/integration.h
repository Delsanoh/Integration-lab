#ifndef INTEGRATION_H
#define INTEGRATION_H

#include <cstdint>

// Подынтегральная функция
double f(double x);

// Методы численного интегрирования
double left_rectangles(double (*func)(double), double a, double b, double eps, int32_t& n_final);
double right_rectangles(double (*func)(double), double a, double b, double eps, int32_t& n_final);
double middle_rectangles(double (*func)(double), double a, double b, double eps, int32_t& n_final);
double trapezoidal(double (*func)(double), double a, double b, double eps, int32_t& n_final);
double simpson(double (*func)(double), double a, double b, double eps, int32_t& n_final);

#endif 