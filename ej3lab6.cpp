#include <iostream>
#include <pthread.h>
#include <cmath>

//estructura para los parametros de cada thread
struct ThreadData {
    int n;
    double result;
};

//funcion ejecutada por cada thread para operar un termino de la serie
void* compute_term(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    int n = data->n;
    //Term: (-1)^(n+1) / n
    data->result = pow(-1, n + 1) / n;
    return nullptr;
}

int main() {
    int N;
    
    //ingreso de max valor de N
    std::cout << "Enter the maximum value of N: ";
    std::cin >> N;

    pthread_t threads[N];
    ThreadData thread_data[N];

    //crea cada thread
    for (int i = 0; i < N; ++i) {
        thread_data[i].n = i + 1;  // n ranges from 1 to N
        pthread_create(&threads[i], nullptr, compute_term, (void*)&thread_data[i]);
    }

    double sum = 0.0;

    //junta cada thread
    for (int i = 0; i < N; ++i) {
        pthread_join(threads[i], nullptr);
        sum += thread_data[i].result;
    }

    //suma total
    std::cout << "La sumatoria es equivalente a: " << sum << std::endl;

    return 0;
}
