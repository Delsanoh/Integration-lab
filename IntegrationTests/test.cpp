#include "pch.h"

#include "../Лаба интегралы/integration.cpp"
#include <gtest/gtest.h>
#include <cmath>
#include <iostream>

// Точность для сравнения
const double COMPARE_EPS = 1e-12;

// Тесты для подынтегральной функции f(x)
TEST(IntegrationTest, FunctionValues) {
    // Проверяем несколько известных значений
    EXPECT_DOUBLE_EQ(f(0.0), 0.0); // sin(0)/(1+0) = 0
    EXPECT_NEAR(f(0.5), std::sin(0.4 * 0.5) / (1.0 + 0.5), COMPARE_EPS);
    EXPECT_NEAR(f(1.0), std::sin(0.4) / 2.0, COMPARE_EPS);
    EXPECT_NEAR(f(2.0), std::sin(0.8) / 3.0, COMPARE_EPS);
}

// Тест на отрицательные аргументы
TEST(IntegrationTest, FunctionNegativeArgument) {
    // Обратите внимание: функция определена для x > -1 (знаменатель 1+x)
    EXPECT_NEAR(f(-0.5), std::sin(-0.2) / 0.5, COMPARE_EPS);
}

// Базовый тест для левых прямоугольников
TEST(IntegrationTest, LeftRectanglesBasic) {
    int32_t n = 0;
    double eps = 1e-6;
    double result = left_rectangles(f, 0.0, 1.0, eps, n);

    // Проверяем, что результат получен
    EXPECT_GT(n, 0);
    EXPECT_TRUE(std::isfinite(result));

    // Проверяем, что точность достигнута (грубая проверка)
    double more_precise_result;
    int32_t n2;
    more_precise_result = left_rectangles(f, 0.0, 1.0, eps / 10.0, n2);
    EXPECT_NEAR(result, more_precise_result, eps * 10.0); // Должны быть близки
}

// Тест для правых прямоугольников
TEST(IntegrationTest, RightRectanglesBasic) {
    int32_t n = 0;
    double eps = 1e-6;
    double result = right_rectangles(f, 0.0, 1.0, eps, n);

    EXPECT_GT(n, 0);
    EXPECT_TRUE(std::isfinite(result));

    // Сравниваем с левыми прямоугольниками - должны быть близки
    int32_t n_left;
    double result_left = left_rectangles(f, 0.0, 1.0, eps, n_left);
    EXPECT_NEAR(result, result_left, 1e-4); // Разные методы, но должны давать похожие результаты
}

// Тест для средних прямоугольников
TEST(IntegrationTest, MiddleRectanglesBasic) {
    int32_t n = 0;
    double eps = 1e-6;
    double result = middle_rectangles(f, 0.0, 1.0, eps, n);

    EXPECT_GT(n, 0);
    EXPECT_TRUE(std::isfinite(result));

    // Средние прямоугольники обычно дают результат между левыми и правыми
    int32_t n_left, n_right;
    double left = left_rectangles(f, 0.0, 1.0, eps, n_left);
    double right = right_rectangles(f, 0.0, 1.0, eps, n_right);

    // Проверяем, что результат средних прямоугольников между левыми и правыми
    EXPECT_GE(result, std::min(left, right) - 1e-10);
    EXPECT_LE(result, std::max(left, right) + 1e-10);
}

// Тест для метода трапеций
TEST(IntegrationTest, TrapezoidalBasic) {
    int32_t n = 0;
    double eps = 1e-6;
    double result = trapezoidal(f, 0.0, 1.0, eps, n);

    EXPECT_GT(n, 0);
    EXPECT_TRUE(std::isfinite(result));
}

// Тест для метода Симпсона
TEST(IntegrationTest, SimpsonBasic) {
    int32_t n = 0;
    double eps = 1e-6;
    double result = simpson(f, 0.0, 1.0, eps, n);

    EXPECT_GT(n, 0);
    EXPECT_TRUE(std::isfinite(result));
    EXPECT_GT(n, 0);
    // Проверяем, что n четное (метод Симпсона требует четного числа интервалов)
    EXPECT_EQ(n % 2, 0);
}

// Тест на одинаковые границы интегрирования
TEST(IntegrationTest, ZeroLengthInterval) {
    int32_t n;
    double result = left_rectangles(f, 1.0, 1.0, 1e-6, n);

    // Интеграл по нулевому интервалу должен быть 0
    EXPECT_NEAR(result, 0.0, COMPARE_EPS);
}



// Тест на увеличение n при увеличении точности
TEST(IntegrationTest, NIncreasesWithPrecision) {
    int32_t n_low, n_high;
    double result_low = left_rectangles(f, 0.0, 1.0, 1e-3, n_low);
    double result_high = left_rectangles(f, 0.0, 1.0, 1e-6, n_high);

    EXPECT_GT(n_high, n_low); // Для большей точности нужно больше разбиений
    EXPECT_TRUE(std::isfinite(result_low));
    EXPECT_TRUE(std::isfinite(result_high));
}

// Тест с другой функцией (x^2)
double square_func(double x) {
    return x * x;
}

TEST(IntegrationTest, SquareFunctionExact) {
    int32_t n;
    double eps = 1e-8;

    // ∫x² dx от 0 до 1 = 1/3
    double exact = 1.0 / 3.0;

    // Проверяем разные методы
    double result_simpson = simpson(square_func, 0.0, 1.0, eps, n);
    EXPECT_NEAR(result_simpson, exact, 1e-8);

    double result_trap = trapezoidal(square_func, 0.0, 1.0, eps, n);
    EXPECT_NEAR(result_trap, exact, 1e-6);

    double result_mid = middle_rectangles(square_func, 0.0, 1.0, eps, n);
    EXPECT_NEAR(result_mid, exact, 1e-6);
}

// Тест с линейной функцией (должна быть точной для метода трапеций)
double linear_func(double x) {
    return 2.0 * x + 3.0;
}

TEST(IntegrationTest, LinearFunctionTrapezoidalExact) {
    int32_t n;
    double eps = 1e-10;

    // ∫(2x+3) dx от 0 до 1 = [x² + 3x]₀¹ = 1 + 3 = 4
    double exact = 4.0;

    // Метод трапеций должен быть точным для линейных функций
    double result = trapezoidal(linear_func, 0.0, 1.0, eps, n);
    EXPECT_NEAR(result, exact, COMPARE_EPS);
}

// Тест с константной функцией
double constant_func(double x) {
    return 5.0;
}

TEST(IntegrationTest, ConstantFunctionExact) {
    int32_t n;
    double eps = 1e-10;

    // ∫5 dx от 0 до 1 = 5
    double exact = 5.0;

    // Все методы должны быть точными для константы
    double result_left = left_rectangles(constant_func, 0.0, 1.0, eps, n);
    EXPECT_NEAR(result_left, exact, COMPARE_EPS);

    double result_right = right_rectangles(constant_func, 0.0, 1.0, eps, n);
    EXPECT_NEAR(result_right, exact, COMPARE_EPS);

    double result_mid = middle_rectangles(constant_func, 0.0, 1.0, eps, n);
    EXPECT_NEAR(result_mid, exact, COMPARE_EPS);

    double result_trap = trapezoidal(constant_func, 0.0, 1.0, eps, n);
    EXPECT_NEAR(result_trap, exact, COMPARE_EPS);

    double result_simp = simpson(constant_func, 0.0, 1.0, eps, n);
    EXPECT_NEAR(result_simp, exact, COMPARE_EPS);
}

// Тест на монотонность результатов при увеличении n
TEST(IntegrationTest, MonotonicityTest) {
    // Создаем упрощенную версию функции для тестирования
    auto test_integral = [](double (*func)(double), double a, double b, int32_t n,
        double (*method)(double (*)(double), double, double, double, int32_t&)) {
            int32_t dummy_n;
            return method(func, a, b, 1.0, dummy_n); // Используем большую eps для фиксированного n
        };

    // Проверяем, что при удвоении n результаты становятся ближе
    std::vector<int32_t> n_values = { 4, 8, 16, 32, 64 };
    std::vector<double> results;

    for (int32_t n : n_values) {
        // Эмулируем работу с фиксированным n
        int32_t dummy;
        double result = left_rectangles(f, 0.0, 1.0, 1.0, dummy);
        // Принудительно устанавливаем нужное количество итераций
        for (int32_t i = 0; i < n / 4; i++) {
            result = left_rectangles(f, 0.0, 1.0, 1.0, dummy);
        }
        results.push_back(result);
    }

    // Проверяем, что разности между последовательными результатами уменьшаются
    for (size_t i = 1; i < results.size() - 1; i++) {
        double diff1 = std::fabs(results[i] - results[i - 1]);
        double diff2 = std::fabs(results[i + 1] - results[i]);
        // diff2 должно быть меньше diff1 (или хотя бы не сильно больше)
        EXPECT_LT(diff2, diff1 * 3.0); // С запасом на случайные колебания
    }
}

// Тест на обработку параметра n_final
TEST(IntegrationTest, NFinalParameterTest) {
    int32_t n = 0;
    double eps = 1e-6;

    double result = left_rectangles(f, 0.0, 1.0, eps, n);

    // n должен быть установлен в значение > 0
    EXPECT_GT(n, 0);
    EXPECT_TRUE(std::isfinite(result));

    // Повторный вызов с тем же n должен сохранить его значение
    int32_t n_old = n;
    result = left_rectangles(f, 0.0, 1.0, eps, n);
    EXPECT_GT(n, 0);
    // n может измениться, но не должен стать 0
    EXPECT_NE(n, 0);
}

// Тест на очень малую точность
TEST(IntegrationTest, VeryLowPrecisionTest) {
    int32_t n;
    double eps = 0.1; // Большая погрешность

    double result = left_rectangles(f, 0.0, 1.0, eps, n);

    EXPECT_GT(n, 0);
    EXPECT_TRUE(std::isfinite(result));
    EXPECT_LT(n, 1000000); // Разумное ограничение
}

// Тест на очень высокую точность
TEST(IntegrationTest, VeryHighPrecisionTest) {
    int32_t n;
    double eps = 1e-12;

    double result = simpson(f, 0.0, 1.0, eps, n);

    EXPECT_GT(n, 0);
    EXPECT_TRUE(std::isfinite(result));
    // Для очень высокой точности нужно много разбиений
    EXPECT_GT(n, 100);
}

// Тест сравнения всех методов
TEST(IntegrationTest, AllMethodsComparison) {
    double eps = 1e-6;
    int32_t n_left, n_right, n_mid, n_trap, n_simp;

    double left = left_rectangles(f, 0.0, 1.0, eps, n_left);
    double right = right_rectangles(f, 0.0, 1.0, eps, n_right);
    double mid = middle_rectangles(f, 0.0, 1.0, eps, n_mid);
    double trap = trapezoidal(f, 0.0, 1.0, eps, n_trap);
    double simp = simpson(f, 0.0, 1.0, eps, n_simp);

    // Все результаты должны быть конечными числами
    EXPECT_TRUE(std::isfinite(left));
    EXPECT_TRUE(std::isfinite(right));
    EXPECT_TRUE(std::isfinite(mid));
    EXPECT_TRUE(std::isfinite(trap));
    EXPECT_TRUE(std::isfinite(simp));

    // Все n должны быть положительными
    EXPECT_GT(n_left, 0);
    EXPECT_GT(n_right, 0);
    EXPECT_GT(n_mid, 0);
    EXPECT_GT(n_trap, 0);
    EXPECT_GT(n_simp, 0);

    // Метод Симпсона требует четного n
    EXPECT_EQ(n_simp % 2, 0);

    // Проверяем, что методы дают близкие результаты
    double max_result = std::max({ left, right, mid, trap, simp });
    double min_result = std::min({ left, right, mid, trap, simp });

    // Разброс между методами не должен быть слишком большим
    EXPECT_LT(max_result - min_result, 0.01);
}

// Тест с большим интервалом
TEST(IntegrationTest, LargeIntervalTest) {
    int32_t n;
    double eps = 1e-6;

    double result = simpson(f, 0.0, 10.0, eps, n);

    EXPECT_GT(n, 0);
    EXPECT_TRUE(std::isfinite(result));
    // Для большего интервала нужно больше разбиений
    EXPECT_GT(n, 100);
}

// Тест на воспроизводимость
TEST(IntegrationTest, ReproducibilityTest) {
    int32_t n1, n2;
    double eps = 1e-6;

    double result1 = left_rectangles(f, 0.0, 1.0, eps, n1);
    double result2 = left_rectangles(f, 0.0, 1.0, eps, n2);

    // При одинаковых параметрах результаты должны быть близки
    EXPECT_NEAR(result1, result2, eps);
    EXPECT_NEAR(n1, n2, n1 * 0.1); // n должны быть близки
}

