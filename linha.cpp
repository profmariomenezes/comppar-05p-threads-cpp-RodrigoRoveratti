#include <iostream>
#include <vector>
#include <pthread.h>
#include <chrono>

#define M 3  // Número de linhas de A
#define N 3  // Número de colunas de A e linhas de B
#define X 3  // Número de colunas de B
#define NUM_THREADS 4

using namespace std;
using namespace chrono;

vector<vector<int>> A(M, vector<int>(N, 1)); // Inicializando com 1 para simplificar
vector<vector<int>> B(N, vector<int>(X, 1));
vector<vector<int>> C(M, vector<int>(X, 0));

struct ThreadData {
    int startRow, endRow;
};

void* multiply(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    for (int i = data->startRow; i < data->endRow; ++i) {
        for (int j = 0; j < X; ++j) {
            for (int k = 0; k < N; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    pthread_exit(NULL);
}

void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

int main() {
    pthread_t threads[NUM_THREADS];
    ThreadData threadData[NUM_THREADS];
    int rowsPerThread = M / NUM_THREADS;

    auto start = high_resolution_clock::now();

    for (int t = 0; t < NUM_THREADS; ++t) {
        threadData[t].startRow = t * rowsPerThread;
        threadData[t].endRow = (t == NUM_THREADS - 1) ? M : (t + 1) * rowsPerThread;
        pthread_create(&threads[t], NULL, multiply, (void*)&threadData[t]);
    }

    for (int t = 0; t < NUM_THREADS; ++t) {
        pthread_join(threads[t], NULL);
    }

    auto end = high_resolution_clock::now();
    duration<double> elapsed = end - start;
    cout << "Tempo de execução: " << elapsed.count() << " segundos" << endl;

    // Exibir resultado da multiplicação
    cout << "Matriz Resultante C:" << endl;
    printMatrix(C);

    return 0;
}
