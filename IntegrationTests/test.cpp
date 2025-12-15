#include "pch.h"
#include <cmath>
#include "../Лаба интегралы/integration.h"
#include "../Лаба интегралы/integration.cpp"


// Тест 1: Проверка подынтегральных функций в конкретных точках
TEST(IntegrationTests, TestFunctionValues) {
    // Проверка f_sin
    EXPECT_NEAR(f_sin(0.5), std::sin(0.4 * 0.5) * std::pow(0.5, 0.23), 1e-10);

    // Проверка f_cubic
    EXPECT_NEAR(f_cubic(0.3), 1.0 / (1.0 + 0.3 * 0.3 * 0.3), 1e-10);

    // Проверка f_exp (особая проверка, избегаем деления на 0)
    EXPECT_NEAR(f_exp(1.0), std::exp(0.1 * 1.0) / 1.0, 1e-10);
}

// Тест 2: Проверка методов интегрирования на простой функции (константа)
TEST(IntegrationTests, TestConstantFunction) {
    // Тестовая функция: f(x) = 2
    auto const_func = [](double x) -> double { return 2.0; };

    double a = 0.0;
    double b = 5.0;
    int32_t n = 100;
    double exact = 2.0 * (b - a); // ∫2dx = 2*(b-a)

    double left_result = left_rectangles(const_func, a, b, n);
    double right_result = right_rectangles(const_func, a, b, n);
    double middle_result = middle_rectangles(const_func, a, b, n);
    double trapez_result = trapezoidal(const_func, a, b, n);
    double simpson_result = simpson(const_func, a, b, n);

    EXPECT_NEAR(left_result, exact, 1e-10);
    EXPECT_NEAR(right_result, exact, 1e-10);
    EXPECT_NEAR(middle_result, exact, 1e-10);
    EXPECT_NEAR(trapez_result, exact, 1e-10);
    EXPECT_NEAR(simpson_result, exact, 1e-10);
}

// Тест 3: Проверка методов интегрирования на линейной функции
TEST(IntegrationTests, TestLinearFunction) {
    // f(x) = 3x + 2, ∫(3x+2)dx от 0 до 4 = [1.5x² + 2x]₀⁴ = 1.5*16 + 8 = 32
    auto linear_func = [](double x) -> double { return 3.0 * x + 2.0; };

    double a = 0.0;
    double b = 4.0;
    int32_t n = 1000; // Больше точек для точности
    double exact = 32.0;

    double left_result = left_rectangles(linear_func, a, b, n);
    double right_result = right_rectangles(linear_func, a, b, n);
    double middle_result = middle_rectangles(linear_func, a, b, n);
    double trapez_result = trapezoidal(linear_func, a, b, n);
    double simpson_result = simpson(linear_func, a, b, n);

    // Для линейной функции метод трапеций и Симпсона должны быть точными
    EXPECT_NEAR(trapez_result, exact, 1e-10);
    EXPECT_NEAR(simpson_result, exact, 1e-10);

    // Прямоугольные методы имеют погрешность
    EXPECT_NEAR(left_result, exact, 0.1);
    EXPECT_NEAR(right_result, exact, 0.1);
    EXPECT_NEAR(middle_result, exact, 0.1);
}

// Тест 4: Проверка сходимости методов (увеличение n уменьшает погрешность)
TEST(IntegrationTests, TestConvergence) {
    // x²dx от 0 до 1 = 1/3 ≈ 0.33333333
    auto square_func = [](double x) -> double { return x * x; };

    double a = 0.0;
    double b = 1.0;
    double exact = 1.0 / 3.0;

    // Разные значения n
    int32_t n_values[] = { 10, 50, 100, 500 };
    double prev_error = 100.0; // Большое начальное значение

    for (int32_t n : n_values) {
        double result = middle_rectangles(square_func, a, b, n);
        double error = std::fabs(result - exact);

        // Проверяем, что ошибка уменьшается с увеличением n
        EXPECT_LT(error, prev_error) << "При n = " << n;
        prev_error = error;
    }
}

// Тест 5: Проверка работы с особыми границами (один и тот же предел)
TEST(IntegrationMethodsTest, ZeroWidthInterval) {
    auto test_func = [](double x) { return std::sin(x); };
    double a = 2.5;
    int32_t n = 10;

    // Интеграл от a до a должен быть 0
    EXPECT_NEAR(left_rectangles(test_func, a, a, n), 0.0, 1e-12);
    EXPECT_NEAR(right_rectangles(test_func, a, a, n), 0.0, 1e-12);
    EXPECT_NEAR(middle_rectangles(test_func, a, a, n), 0.0, 1e-12);
    EXPECT_NEAR(trapezoidal(test_func, a, a, n), 0.0, 1e-12);
    EXPECT_NEAR(simpson(test_func, a, a, n), 0.0, 1e-12);
}

// Тест 6: Проверка методов на квадратичной функции (Симпсон должен быть точным)
TEST(IntegrationTests, TestQuadraticFunction) {
    // f(x) = 2x² + 3x + 1
    // (2x² + 3x + 1)dx от 1 до 3 = [2x³/3 + 3x²/2 + x]₁³
    auto quadratic_func = [](double x) -> double {
        return 2.0 * x * x + 3.0 * x + 1.0;
        };

    double a = 1.0;
    double b = 3.0;
    int32_t n = 10; // Четное число для Симпсона
    double exact = (2.0 * b * b * b / 3.0 + 3.0 * b * b / 2.0 + b) -
        (2.0 * a * a * a / 3.0 + 3.0 * a * a / 2.0 + a);

    double simpson_result = simpson(quadratic_func, a, b, n);

    // Метод Симпсона должен быть точным для квадратичных функций
    EXPECT_NEAR(simpson_result, exact, 1e-12);
}

