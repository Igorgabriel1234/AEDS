#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>

using namespace std;
using namespace std::chrono;

// Funções de ordenação
void bubbleSort(int arr[], int n);
void bubbleSortMelhorado(int arr[], int n);
void selectionSort(int arr[], int n);
void insertionSort(int arr[], int n);
void quickSort(int arr[], int low, int high);
int partition(int arr[], int low, int high);

// Funções auxiliares
void carregarDados(const string& filename, int arr[], int n);
bool verificarOrdenacao(int arr[], int n);
double medirTempoExecucao(void (*sortFunc)(int[], int), int arr[], int n, const string& nomeAlgoritmo);
double medirTempoExecucaoQuick(void (*sortFunc)(int[], int, int), int arr[], int low, int high, const string& nomeAlgoritmo);

int main() {
    const int TAMANHO = 100000;
    int arrAleatorio[TAMANHO];
    int arrCrescente[TAMANHO];

    // Carregar os dados
    carregarDados("aleat_100000.txt", arrAleatorio, TAMANHO);
    carregarDados("cresc_100000.txt", arrCrescente, TAMANHO);

    // Executar e medir o tempo dos algoritmos com os dados aleatórios
    double tempoAleatorioQuick = medirTempoExecucaoQuick(quickSort, arrAleatorio, 0, TAMANHO - 1, "Quick Sort Aleatório");

    // Recarregar os dados para o próximo teste com o array crescente
    double tempoCrescenteQuick = medirTempoExecucaoQuick(quickSort, arrCrescente, 0, TAMANHO - 1, "Quick Sort Crescente");

    // Comparar os tempos
    cout << "Tempo Quick Sort Aleatório: " << tempoAleatorioQuick << " segundos" << endl;
    cout << "Tempo Quick Sort Crescente: " << tempoCrescenteQuick << " segundos" << endl;
    
    if (tempoAleatorioQuick > tempoCrescenteQuick) {
        cout << "O Quick Sort com dados aleatórios foi " << tempoAleatorioQuick - tempoCrescenteQuick << " segundos mais lento." << endl;
    } else {
        cout << "O Quick Sort com dados crescentes foi " << tempoCrescenteQuick - tempoAleatorioQuick << " segundos mais lento." << endl;
    }

    return 0;
}

void carregarDados(const string& filename, int arr[], int n) {
    ifstream file(filename);
    for (int i = 0; i < n && file >> arr[i]; ++i);
    file.close();
}

bool verificarOrdenacao(int arr[], int n) {
    for (int i = 1; i < n; ++i) {
        if (arr[i-1] > arr[i]) return false;
    }
    return true;
}

double medirTempoExecucao(void (*sortFunc)(int[], int), int arr[], int n, const string& nomeAlgoritmo) {
    clock_t start = clock(); // clock inicializado
    sortFunc(arr, n);
    clock_t end = clock();

    double duration = double(end - start) / CLOCKS_PER_SEC; // cálculo do tempo em segundos
    cout << nomeAlgoritmo << " levou " << duration << " segundos para executar." << endl;

    if (verificarOrdenacao(arr, n)) {
        cout << "Ordenação correta." << endl;
    } else {
        cout << "Erro na ordenação!" << endl;
    }

    return duration;
}

double medirTempoExecucaoQuick(void (*sortFunc)(int[], int, int), int arr[], int low, int high, const string& nomeAlgoritmo) {
    clock_t start = clock(); // clock inicializado
    sortFunc(arr, low, high);
    clock_t end = clock();

    double duration = double(end - start) / CLOCKS_PER_SEC; // cálculo do tempo em segundos
    cout << nomeAlgoritmo << " levou " << duration << " segundos para executar." << endl;

    if (verificarOrdenacao(arr, high - low + 1)) {
        cout << "Ordenação correta." << endl;
    } else {
        cout << "Erro na ordenação!" << endl;
    }

    return duration;
}

// Implementação dos algoritmos de ordenação

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
            }
        }
    }
}

void bubbleSortMelhorado(int arr[], int n) {
    bool swapped;
    for (int i = 0; i < n-1; i++) {
        swapped = false;
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        int minIndex = i;
        for (int j = i+1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        swap(arr[minIndex], arr[i]);
    }
}

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}
