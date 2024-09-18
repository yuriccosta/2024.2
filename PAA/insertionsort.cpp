#include <iostream>
#include <vector>
#include <ctime>


void insertionSort(std::vector<int>& A) {
    int n = A.size();
    for (int j = 1; j < n; j++) { //Observe que j começa de 1 //n
        int key = A[j]; //Assume a chave, isto é, o elemento que vamos comparar //n - 1
        int i = j - 1;//Define i como  j -1, ou seja, o indice anterior // n - 1
        // Insere A[j] na sequência ordenada A[0..j-1]
        while (i >= 0 && A[i] > key) { // Somatório de j=1 até n 
            A[i + 1] = A[i]; //Move para direita, o que abre espaço para key
            i = i - 1; //Atualiza o valor de i para que o proximo item do vetor seja comparado
        }
        A[i + 1] = key; //Ao final do loop i será i<0, ou seja, key vai para A[0], é o menor elemento
                        //ou A[i]<=key, isto é, A[i] é menor ou igual a key, portanto, key fica a direia de A[i], posicao já correta

    } //O loop externo acaba porque j quando atinge o tamanho de n, isto é, o tamanho do vetor
}

int main(int argc, char *argv[]) {
    

    double timeResult = 0.0;
    double startTime = 0.0;
    double endTime = 0.0;
    const int nCycles = atoi(argv[1]);

    std::vector<int> A;
    for (int i = 0; i < nCycles; i++){
        A.push_back(rand());
    }

    startTime = clock();
    insertionSort(A);
    endTime = clock();
    timeResult = (endTime / CLOCKS_PER_SEC) - (startTime / CLOCKS_PER_SEC);
    std::cout << nCycles <<" Tempo: " << timeResult << std::endl;
    return 0;
}