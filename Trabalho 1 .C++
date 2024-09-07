#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Funções de ordenação
void bubbleSort(int arr[], int n);
void bubbleSortMelhorado(int arr[], int n);
void selectionSort(int arr[], int n);
void insertionSort(int arr[], int n);
void quicksort(int v[], int left, int right);

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
    cout << "Algoritmos com dados Aleatórios:\n";
    medirTempoExecucao(bubbleSort, arrAleatorio, TAMANHO, "Bubble Sort");
    carregarDados("aleat_100000.txt", arrAleatorio, TAMANHO);  // Recarregar dados para evitar ordenar o array já ordenado
    medirTempoExecucao(bubbleSortMelhorado, arrAleatorio, TAMANHO, "Bubble Sort Melhorado");
    carregarDados("aleat_100000.txt", arrAleatorio, TAMANHO);
    medirTempoExecucao(selectionSort, arrAleatorio, TAMANHO, "Selection Sort");
    carregarDados("aleat_100000.txt", arrAleatorio, TAMANHO);
    medirTempoExecucao(insertionSort, arrAleatorio, TAMANHO, "Insertion Sort");
    carregarDados("aleat_100000.txt", arrAleatorio, TAMANHO);
    medirTempoExecucaoQuick(quicksort, arrAleatorio, 0, TAMANHO - 1, "Quick Sort");

    // Recarregar os dados para o próximo teste com o array crescente
    cout << "\nAlgoritmos com dados Crescentes:\n";
    carregarDados("cresc_100000.txt", arrCrescente, TAMANHO);
    medirTempoExecucao(bubbleSort, arrCrescente, TAMANHO, "Bubble Sort com Crescente");
    carregarDados("cresc_100000.txt", arrCrescente, TAMANHO); 
    medirTempoExecucao(bubbleSortMelhorado, arrCrescente, TAMANHO, "Bubble Sort Melhorado com Crescente");
    carregarDados("cresc_100000.txt", arrCrescente, TAMANHO); 
    medirTempoExecucao(selectionSort, arrCrescente, TAMANHO, "Selection Sort com Crescente");
    carregarDados("cresc_100000.txt", arrCrescente, TAMANHO); 
    medirTempoExecucao(insertionSort, arrCrescente, TAMANHO, "Insertion Sort com Crescente");
    carregarDados("cresc_100000.txt", arrCrescente, TAMANHO);
    medirTempoExecucaoQuick(quicksort, arrCrescente, 0, TAMANHO - 1, "Quick Sort com Crescente");

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
    auto start = high_resolution_clock::now(); // clock inicializado
    sortFunc(arr, n);
    auto end = high_resolution_clock::now();

    double duration = duration_cast<milliseconds>(end - start).count(); // cálculo do tempo em milissegundos
    cout << nomeAlgoritmo << " levou " << duration << " ms para executar." << endl;

    if (verificarOrdenacao(arr, n)) {
        cout << "Ordenação correta." << endl;
    } else {
        cout << "Erro na ordenação!" << endl;
    }

    return duration;
}

double medirTempoExecucaoQuick(void (*sortFunc)(int[], int, int), int arr[], int low, int high, const string& nomeAlgoritmo) {
    auto start = high_resolution_clock::now(); // clock inicializado
    sortFunc(arr, low, high);
    auto end = high_resolution_clock::now();

    double duration = duration_cast<milliseconds>(end - start).count(); // cálculo do tempo em milissegundos
    cout << nomeAlgoritmo << " levou " << duration << " ms para executar." << endl;

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

// Função quicksort conforme o exemplo da imagem
void quicksort(int v[], int left, int right) {
    int pivo = v[(left + right) / 2];
    int i = left;
    int j = right;

    do {
        while (v[i] < pivo) i++;
        while (v[j] > pivo) j--;

        if (i <= j) {
            int aux = v[i];
            v[i] = v[j];
            v[j] = aux;
            i++;
            j--;
        }
    } while (i <= j);

    if (left < j) quicksort(v, left, j);
    if (i < right) quicksort(v, i, right);
}
