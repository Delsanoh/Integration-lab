#include <iostream>
#include <cmath>
#include <iomanip>
#include <cstdint>
#include <locale>
#include "integration.h"

int main() {
    std::setlocale(LC_ALL, "Russian");
    double a = 0.0;
    double b = 1.0;
    double eps = 1e-6;
    int32_t n;

    std::cout << "Вычисление интеграла: [0,1] sin(0.4x)/(1+x) dx" << std::endl;
    std::cout << "Точность: " << eps << std::endl;
    std::cout << "Эталонное значение: 0.17686418" << std::endl;
    std::cout << std::string(60, '=') << std::endl;

    double result = left_rectangles(f, a, b, eps, n);
    std::cout << std::fixed << std::setprecision(8);
    std::cout << "A) Левые прямоугольники: " << result << std::endl;
    std::cout << "   n = " << n << ", погрешность = " << std::fabs(result - 0.17686418) << std::endl;

    result = right_rectangles(f, a, b, eps, n);
    std::cout << "Б) Правые прямоугольники: " << result << std::endl;
    std::cout << "   n = " << n << ", погрешность = " << std::fabs(result - 0.17686418) << std::endl;

    result = middle_rectangles(f, a, b, eps, n);
    std::cout << "В) Средние прямоугольники: " << result << std::endl;
    std::cout << "   n = " << n << ", погрешность = " << std::fabs(result - 0.17686418) << std::endl;

    result = trapezoidal(f, a, b, eps, n);
    std::cout << "Г) Трапеции: " << result << std::endl;
    std::cout << "   n = " << n << ", погрешность = " << std::fabs(result - 0.17686418) << std::endl;

    result = simpson(f, a, b, eps, n);
    std::cout << "Д) Симпсон: " << result << std::endl;
    std::cout << "   n = " << n << ", погрешность = " << std::fabs(result - 0.17686418) << std::endl;

    return 0;
}