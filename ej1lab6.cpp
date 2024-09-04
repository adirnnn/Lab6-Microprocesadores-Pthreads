#include <iostream>
#include <pthread.h>
#include <vector>

struct ThreadData {
    int limit;
    std::vector<int> fibonacciNumbers;
    int sum;
};

void* calculateFibonacci(void* params) {
    ThreadData* data = (ThreadData*)params;
    int a = 0, b = 1, next = 0;
    data->sum = 0;

    for (int i = 0; i <= data->limit; ++i) {
        if (next > data->limit) {
            break;
        }
        data->fibonacciNumbers.push_back(next);  // agrega el numero al vector.
        data->sum += next;                       // suma el numero al total.
        a = b;
        b = next;
        next = a + b;  // calcula el siguiente numero
    }

    pthread_exit(NULL);  // termina el hilo.
    return NULL;
}

int main() {
    int limit;  // variable donde se almacena el límite ingresado por el usuario.
    std::cout << "Ingrese un numero entre 0 y 100: ";
    std::cin >> limit;

    // verificacion del rango
    if (limit < 0 || limit > 100) {
        std::cout << "El numero debe estar entre 0 y 100." << std::endl;
        return 1;
    }

    // inicializa la estructura de datos.
    ThreadData data;
    data.limit = limit;
    data.sum = 0;

    pthread_t thread; 
    // crea un hilo para ejecutar la función calculateFibonacci.
    int rc = pthread_create(&thread, NULL, calculateFibonacci, &data);
    if (rc) {
        std::cout << "Error: No se pudo crear el hilo, codigo de error: " << rc << std::endl;
        return 1;
    }

    pthread_join(thread, NULL);

    std::cout << "Números de la serie Fibonacci hasta " << limit << ":" << std::endl;
    for (size_t i = 0; i < data.fibonacciNumbers.size(); ++i) {
        std::cout << "Iteración " << i + 1 << ": " << data.fibonacciNumbers[i] << std::endl;
    }
    std::cout << "Suma total de los números de Fibonacci: " << data.sum << std::endl;

    return 0;
}