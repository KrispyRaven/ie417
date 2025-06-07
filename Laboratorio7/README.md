# Informe de Laboratorio 7: Herramientas de Depuración
### Alison Rivera Cisneros C06510
### Noel Blandon Saborio B61097
### Ricardo Hidalgo Campos B63464

## Introducción

En este laboratorio se ejecutaron los códigos referentes al tema de **depuración**, específicamente usando herramientas como `gdb`, `valgrind`, `AddressSanitizer`, `ThreadSanitizer` y `Helgrind`. El objetivo fue identificar errores de ejecución, pérdidas de memoria, condiciones de carrera y otros defectos de programación descritos en la presentación suministrada.

---

## gdb (GNU Debugger)

`gdb` es una herramienta potente para depurar programas en C y C++. Permite ejecutar el código paso a paso, inspeccionar variables, establecer puntos de interrupción y analizar la pila de llamadas. En este laboratorio, se utilizó para detectar un error de división por cero.

**Cómo se usó:**  
Se compiló el programa con la bandera `-g`, se inició con `gdb`, se estableció un punto de interrupción y se utilizó `next`, `step`, `print`, `backtrace` para explorar el flujo de ejecución y las variables. Tambien se empleo el entorno virtual onlinegdb.com

### Código:
```cpp
#include <iostream>

void funcion1() {
    int a = 5;
    int b = 0;
    int c = a / b; // Error: División por cero
    std::cout << "Resultado: " << c << std::endl;
}

int main() {
    std::cout << "Iniciando el programa" << std::endl;
    funcion1();
    std::cout << "Finalizando el programa" << std::endl;
    return 0;
}
```

### Implementación:
![image](https://github.com/user-attachments/assets/c630c133-f84d-45b9-afee-9666e8632a04)

![image](https://github.com/user-attachments/assets/1fe6f607-394b-4527-986c-3c40ba360104)



---

## Valgrind

Valgrind es un marco para análisis dinámico de memoria. Se utilizó su herramienta `memcheck` para detectar pérdidas de memoria, errores de lectura/escritura y accesos inválidos.

**Cómo se usó:**  
El programa fue compilado con `-g` y ejecutado con:
```bash
valgrind --leak-check=yes ./programa
```
Esto permitió detectar si se estaba usando memoria sin liberar o accediendo fuera de límites.

### Código:
```cpp
#include <iostream>

void funcion1() {
    int* p = new int[10]; // Pérdida de memoria: no se libera la memoria
    std::cout << p[0] << std::endl; // Uso de memoria no inicializada

    int array[5];
    array[5] = 10; // Acceso fuera de los límites del array
}

int main() {
    funcion1();
    return 0;
}

```

### Implementación:
![image](https://github.com/user-attachments/assets/87f96dca-b1f0-4de3-9d5b-17664395e751)
![image](https://github.com/user-attachments/assets/f442d774-d186-4a74-a374-2db45a8dbe78)


---

## Sanitizer (ASan)

AddressSanitize es una herramienta que detecta errores comunes de memoria como uso de memoria después de ser liberada o accesos fuera de límites.

**Cómo se usó:**  
Se compiló el código con:
```bash
g++ -fsanitize=address -g -o programa programa.cpp
./programa
```
y se observó la salida detallada sobre errores de memoria.

### Código:
```cpp
#include <iostream>

void funcion1() {
    int* p = new int[10];
    p[10] = 5; // Acceso fuera de los límites del array
    delete[] p;

    int* q = new int[10];
    delete[] q;
    std::cout << q[0] << std::endl; // Uso después de liberar memoria
}

int main() {
    funcion1();
    return 0;
}

```

### Implementación:
![image](https://github.com/user-attachments/assets/dd67d604-bd4c-4e74-8e6d-00b8a06109b6)


---

## ThreadSanitizer (TSan)

TSan detecta condiciones de carrera y otros errores relacionados con concurrencia en programas multihilo.

**Cómo se usó:**  
El programa se compiló con:
```bash
g++ -fsanitize=thread -g -o programa programa.cpp
./programa
```
y permitió identificar accesos simultáneos sin sincronización.

### Código:
```cpp
#include <iostream>
#include <thread>

int counter = 0;

void increment() {
    for (int i = 0; i < 100000; ++i) {
        ++counter; // Condición de carrera
    }
}

int main() {
    std::thread t1(increment);
    std::thread t2(increment);

    t1.join();
    t2.join();

    std::cout << "Counter: " << counter << std::endl;
    return 0;
}
```

### Implementación:
![5053511353322549122](https://github.com/user-attachments/assets/4ab6d0f4-2b0a-4cb3-a0e4-fb6ab5c6d411)
![5051334157090795299](https://github.com/user-attachments/assets/1bafddbd-f431-473a-87ff-424adc03f887)


---

## Helgrind

Helgrind es una herramienta de Valgrind enfocada en detectar condiciones de carrera. Es útil para depurar programas multihilo.

**Cómo se usó:**  
Se compiló el programa y se ejecutó con:
```bash
valgrind --tool=helgrind ./programa
```

### Código (rev1):
```cpp
#include <iostream>
#include <thread>

int counter = 0;

void increment() {
    for (int i = 0; i < 100000; ++i) {
        ++counter; // Condition de carrera
    }
}

int main() {
    std::thread t1(increment);
    std::thread t2(increment);

    t1.join();
    t2.join();

    std::cout << "Counter: " << counter << std::endl;
    return 0;
}
```

### Código (rev2):
```cpp
#include <iostream>
#include <thread>
#include <mutex>

int counter = 0;
std::mutex mtx;

void increment() {
    for (int i = 0; i < 100000; ++i) {
        std::lock_guard<std::mutex> lock(mtx);
        ++counter; // Protección del acceso a la variable compartida
    }
}

int main() {
    std::thread t1(increment);
    std::thread t2(increment);

    t1.join();
    t2.join();

    std::cout << "Counter: " << counter << std::endl;
    return 0;
}

```

### Implementación (rev1):
![image](https://github.com/user-attachments/assets/9bd6a164-efde-4057-bb18-5a5e680961a9)
![image](https://github.com/user-attachments/assets/b02ac542-779c-401f-94fb-ac2b71b7449d)


### Implementación (rev2):
![image](https://github.com/user-attachments/assets/34a4098e-f6dd-44b9-b26b-1c5aa47c8154)
