/**
 * @file Calculadora.h
 * @brief Definición de la clase Calculadora.
 */

 #ifndef CALCULADORA_H
 #define CALCULADORA_H
 
 /**
  * @class Calculadora
  * @brief Clase que implementa operaciones aritméticas básicas.
  */
 class Calculadora {
 public:
     /**
      * @brief Suma dos números.
      * @param a Primer número.
      * @param b Segundo número.
      * @return Resultado de a + b.
      */
     double sumar(double a, double b);
 
     /**
      * @brief Resta dos números.
      * @param a Minuendo.
      * @param b Sustraendo.
      * @return Resultado de a - b.
      */
     double restar(double a, double b);
 
     /**
      * @brief Multiplica dos números.
      * @param a Primer número.
      * @param b Segundo número.
      * @return Resultado de a * b.
      */
     double multiplicar(double a, double b);
 
     /**
      * @brief Divide dos números.
      * @param a Dividendo.
      * @param b Divisor (debe ser diferente de cero).
      * @return Resultado de a / b. Si b == 0, lanza una excepción.
      */
     double dividir(double a, double b);
 };
 
 #endif // CALCULADORA_H
 