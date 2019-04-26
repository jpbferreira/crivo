#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <pthread.h>

const int n = 50;
int numerosNaoMarcados[] = {};

void *crivo(void *k) {

    int *valork = (int*) k;

    do {

        for (int i = *valork-1; i < n; i++) {
            if (numerosNaoMarcados[i] != 0 && numerosNaoMarcados[i]%*valork == 0) {
                numerosNaoMarcados[i] = 0;
            }
        }

        for (int i = *valork-1; i < n; i++) {
            if (numerosNaoMarcados[i] != 0) {
                *valork = numerosNaoMarcados[i];
                break;
            }
        }

    } while(pow(*valork, 2) < n);
}

void preencheVetor() {
    for(int i = 0; i < n; i++) {
        numerosNaoMarcados[i] = i+2;
    }
}

int main() {

    preencheVetor();

    const int NUMERO_THREADS = sqrt(n);
    
    pthread_t thread[NUMERO_THREADS]; 

    for(int i = 0; i < NUMERO_THREADS; i++) {
        int k = (i+2);
        pthread_create(&thread[i], NULL, crivo, (int*) &k); 
    }

    for(int i = 0; i < NUMERO_THREADS; i++)
        pthread_join(thread[i], NULL);  

    printf("Numeros primos: ");
    for(int i = 0; i < n; i++) {
        if(numerosNaoMarcados[i] != 0)
            printf("%d ", numerosNaoMarcados[i]);
    }
    printf("\n");

    return 0;
}