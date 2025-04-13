/**
 * @file main.cpp  
 * @brief Programa principal que utiliza la clase Calculadora.
 */

#include <iostream>
#include "Calculadora.h"
/**
 * @file main.cpp
 * @details Este programa crea una instancia de la clase Calculadora
 */


int main() {

    /**
     * @brief Programa principal que utiliza la clase Calculadora.
     * @details Este programa crea una instancia de la clase Calculadora
     * y realiza algunas operaciones aritméticas básicas.
     */
    Calculadora calc;
    double a = 10.0, b = 2.0;

    std::cout << "Suma: " << calc.sumar(a, b) << std::endl;
    std::cout << "Resta: " << calc.restar(a, b) << std::endl;
    std::cout << "Multiplicación: " << calc.multiplicar(a, b) << std::endl;
    std::cout << "División: " << calc.dividir(a, b) << std::endl;

    return 0;
}
