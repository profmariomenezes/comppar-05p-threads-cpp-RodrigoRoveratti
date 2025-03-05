#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

#define M 5  // Número de linhas de A
#define N 5  // Número de colunas de A e linhas de B
#define X 5  // Número de colunas de B
#define NUM_THREADS 4
#define BLOCK_SIZE 50  // Tamanho do bloco para otimização de cache

using namespace std;
using namespace chrono;

vector<vector<int>> A(M, vector<int>(N, 1)); // Inicializando com 1 para simplificar
vector<vector<int>> B(N, vector<int>(X, 1));
vector<vector<int>> C(M, vector<int>(X, 0));

struct ThreadData {
    int startRow, endRow;
};

void* multiply_blocked(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    for (int i = data->startRow; i < data->endRow; i += BLOCK_SIZE) {
        for (int j = 0; j < X; j += BLOCK_SIZE) {
            for (int k = 0; k < N; k += BLOCK_SIZE) {
                for (int ii = i; ii < min(i + BLOCK_SIZE, data->endRow); ++ii) {
                    for (int jj = j; jj < min(j + BLOCK_SIZE, X); ++jj) {
                        for (int kk = k; kk < min(k + BLOCK_SIZE, N); ++kk) {
                            C[ii][jj] += A[ii][kk] * B[kk][jj];
                        }
                    }
                }
            }
        }
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    ThreadData threadData[NUM_THREADS];
    int rowsPerThread = M / NUM_THREADS;

    auto start = high_resolution_clock::now();

    for (int t = 0; t < NUM_THREADS; ++t) {
        threadData[t].startRow = t * rowsPerThread;
        threadData[t].endRow = (t == NUM_THREADS - 1) ? M : (t + 1) * rowsPerThread;
        pthread_create(&threads[t], NULL, multiply_blocked, (void*)&threadData[t]);
    }

    for (int t = 0; t < NUM_THREADS; ++t) {
        pthread_join(threads[t], NULL);
    }

    auto end = high_resolution_clock::now();
    duration<double> elapsed = end - start;
    cout << "Tempo de execução (blocagem): " << elapsed.count() << " segundos" << endl;

    // Exibir a matriz resultante C
    cout << "Matriz Resultado C:" << endl;
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < X; ++j) {
            cout << C[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
