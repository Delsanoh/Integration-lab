#include <iostream>
#include <cmath>
#include <iomanip>
#include <cstdint>
#include <locale>
#include "integration.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

int main() {
    std::setlocale(LC_ALL, "Russian");

    // Структура для хранения информации об интеграле
    struct Integral {
        std::string name;
        double (*func)(double);
        double a, b;
        double exact_value;
        std::string formula;
    };

    // Определяем три интеграла
    Integral integrals[] = {
        {
            "Интеграл с экспонентой",
            f_exp,
            0.5, M_PI / 2.0,  // границы: от 0.5 до π/2
            1.2037982,
            "[0.5, π/2] e^(0.1x)/x dx"
        },
        {
            "Интеграл с синусом",
            f_sin,
            0.0, 1.0,  // границы: от 0 до 1
            0.17686418,
            "[0,1] sin(0.4x)·x^0.23 dx"
        },
        {
            "Интеграл с x³",
            f_cubic,
            0.0, 1.0,  // границы: от 0 до 1
            0.83564885,
            "[0,1] 1/(1+x³) dx"
        }
    };

    // Различные значения n для исследования точности
    int32_t n_values[] = { 10, 20, 40, 80, 160, 320 };

    //Вычисление интегралов разными методами для разных n
    for (const auto& integral : integrals) {
        std::cout << "\n" << std::string(60, '=') << std::endl;
        std::cout << integral.name << std::endl;
        std::cout << "Формула: " << integral.formula << std::endl;
        std::cout << "Точное значение: " << std::fixed << std::setprecision(8)
            << integral.exact_value << std::endl;
        std::cout << std::string(60, '-') << std::endl;

        // Заголовок таблицы
        std::cout << std::setw(10) << "n"
            << std::setw(20) << "Лев.прям"
            << std::setw(20) << "Прав.прям"
            << std::setw(20) << "Ср.прям"
            << std::setw(20) << "Трапеции"
            << std::setw(20) << "Симпсон"
            << std::endl;

        // Строки таблицы для каждого n
        for (int32_t n : n_values) {
            double left = left_rectangles(integral.func, integral.a, integral.b, n);
            double right = right_rectangles(integral.func, integral.a, integral.b, n);
            double middle = middle_rectangles(integral.func, integral.a, integral.b, n);
            double trapez = trapezoidal(integral.func, integral.a, integral.b, n);
            double simp = simpson(integral.func, integral.a, integral.b, n);

            std::cout << std::setw(10) << n
                << std::setw(20) << std::setprecision(8) << left
                << std::setw(20) << std::setprecision(8) << right
                << std::setw(20) << std::setprecision(8) << middle
                << std::setw(20) << std::setprecision(8) << trapez
                << std::setw(20) << std::setprecision(8) << simp
                << std::endl;
        }
    }

    //Сравнение погрешностей для фиксированного n=100
    std::cout << "\n" << std::string(60, '=') << std::endl;
    std::cout << "Сравнение погрешностей при n=100:" << std::endl;
    std::cout << std::string(60, '-') << std::endl;

    std::cout << std::setw(30) << "Метод"
        << std::setw(20) << "Интеграл 1"
        << std::setw(20) << "Интеграл 2"
        << std::setw(20) << "Интеграл 3"
        << std::endl;

    int32_t n = 100;

    // Массив названий методов
    const char* methods[] = {
        "Левые прямоугольники",
        "Правые прямоугольники",
        "Средние прямоугольники",
        "Метод трапеций",
        "Метод Симпсона"
    };

    // Вычисляем и выводим погрешности для каждого метода
    for (int method_idx = 0; method_idx < 5; method_idx++) {
        std::cout << std::setw(30) << methods[method_idx];

        for (int integral_idx = 0; integral_idx < 3; integral_idx++) {
            double result;
            const auto& integral = integrals[integral_idx];

            // Выбираем метод интегрирования
            switch (method_idx) {
            case 0:
                result = left_rectangles(integral.func, integral.a, integral.b, n);
                break;
            case 1:
                result = right_rectangles(integral.func, integral.a, integral.b, n);
                break;
            case 2:
                result = middle_rectangles(integral.func, integral.a, integral.b, n);
                break;
            case 3:
                result = trapezoidal(integral.func, integral.a, integral.b, n);
                break;
            case 4:
                result = simpson(integral.func, integral.a, integral.b, n);
                break;
            }

            // Вычисляем абсолютную погрешность
            double error = std::fabs(result - integral.exact_value);
            std::cout << std::setw(20) << std::scientific << std::setprecision(2) << error;
        }
        std::cout << std::endl;
    }

    // Дополнительно: вывод значений для n=100
    std::cout << "\n" << std::string(60, '-') << std::endl;
    std::cout << "Значения интегралов при n=100:" << std::endl;

    n = 100;
    for (int i = 0; i < 3; i++) {
        const auto& integral = integrals[i];
        std::cout << "\n" << integral.name << ":" << std::endl;

        double simp_result = simpson(integral.func, integral.a, integral.b, n);
        double error = std::fabs(simp_result - integral.exact_value);

        std::cout << "  Метод Симпсона: " << std::fixed << std::setprecision(8) << simp_result << std::endl;
        std::cout << "  Точное значение: " << std::fixed << std::setprecision(8) << integral.exact_value << std::endl;
        std::cout << "  Погрешность: " << std::scientific << std::setprecision(2) << error << std::endl;
    }

    return 0;
}