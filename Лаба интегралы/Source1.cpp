#include <iostream>
#include <cmath>
#include <iomanip>
#include <cstdint>
#include <locale>
#include "integration.h"

int main() {
    std::setlocale(LC_ALL, "Russian");
    
    // Параметры для каждого интеграла
    struct Integral {
        std::string name;
        double (*func)(double);
        double a, b;
        double exact_value;
        std::string formula;
    };
    
    Integral integrals[] = {
        {
            "Интеграл с экспонентой",
            f_exp,
            0.5, M_PI/2.0,
            1.2037982,
            "∫[0.5, π/2] e^(0.1x)/x dx"
        },
        {
            "Интеграл с синусом",
            f_sin,
            0.0, 1.0,
            0.17686418,
            "∫[0,1] sin(0.4x)·x^0.23 dx"
        },
        {
            "Интеграл с x³",
            f_cubic,
            0.0, 1.0,
            0.83564885,
            "∫[0,1] 1/(1+x³) dx"
        }
    };
    
    // Различные значения n для исследования точности
    int32_t n_values[] = {10, 20, 40, 80, 160, 320};
    
    for (const auto& integral : integrals) {
        std::cout << "\n" << std::string(60, '=') << std::endl;
        std::cout << integral.name << std::endl;
        std::cout << "Формула: " << integral.formula << std::endl;
        std::cout << "Точное значение: " << std::fixed << std::setprecision(8) 
                  << integral.exact_value << std::endl;
        std::cout << std::string(60, '-') << std::endl;
        
        std::cout << std::setw(10) << "n" 
                  << std::setw(20) << "Лев.прям" 
                  << std::setw(20) << "Ср.прям" 
                  << std::setw(20) << "Трапеции" 
                  << std::setw(20) << "Симпсон" 
                  << std::endl;
        
        for (int32_t n : n_values) {
            double left = left_rectangles(integral.func, integral.a, integral.b, n);
            double middle = middle_rectangles(integral.func, integral.a, integral.b, n);
            double trapez = trapezoidal(integral.func, integral.a, integral.b, n);
            double simp = simpson(integral.func, integral.a, integral.b, n);
            
            std::cout << std::setw(10) << n 
                      << std::setw(20) << std::setprecision(8) << left
                      << std::setw(20) << std::setprecision(8) << middle
                      << std::setw(20) << std::setprecision(8) << trapez
                      << std::setw(20) << std::setprecision(8) << simp
                      << std::endl;
        }
    }
    
    // Дополнительно: сравнение погрешностей для n=100
    std::cout << "\n" << std::string(60, '=') << std::endl;
    std::cout << "Сравнение погрешностей при n=100:" << std::endl;
    std::cout << std::string(60, '-') << std::endl;
    
    std::cout << std::setw(30) << "Метод" 
              << std::setw(20) << "Интеграл 1" 
              << std::setw(20) << "Интеграл 2" 
              << std::setw(20) << "Интеграл 3" 
              << std::endl;
    
    int32_t n = 100;
    std::string methods[] = {"Левые прямоуг.", "Правые прямоуг.", "Средние прямоуг.", 
                            "Трапеции", "Симпсон"};
    
    for (int i = 0; i < 5; i++) {
        std::cout << std::setw(30) << methods[i];
        
        for (int j = 0; j < 3; j++) {
            double result;
            switch(i) {
                case 0: result = left_rectangles(integrals[j].func, integrals[j].a, integrals[j].b, n); break;
                case 1: result = right_rectangles(integrals[j].func, integrals[j].a, integrals[j].b, n); break;
                case 2: result = middle_rectangles(integrals[j].func, integrals[j].a, integrals[j].b, n); break;
                case 3: result = trapezoidal(integrals[j].func, integrals[j].a, integrals[j].b, n); break;
                case 4: result = simpson(integrals[j].func, integrals[j].a, integrals[j].b, n); break;
            }
            double error = std::fabs(result - integrals[j].exact_value);
            std::cout << std::setw(20) << std::setprecision(8) << error;
        }
        std::cout << std::endl;
    }
    
    return 0;
}    result = simpson(f, a, b, eps, n);
    std::cout << "Д) Симпсон: " << result << std::endl;
    std::cout << "   n = " << n << ", погрешность = " << std::fabs(result - 0.17686418) << std::endl;

    return 0;
}
