#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <pthread.h>

int TAM = 8;
int n = 10;
int numerosNaoMarcados[] = {2, 3, 4, 5, 6, 7, 8, 9, 10};

void *crivo() {

    int valork = 2;

    do {

        for (int i = valork-1; i < TAM; i++) {
            if (numerosNaoMarcados[i] != 0 && numerosNaoMarcados[i]%valork == 0) {
                numerosNaoMarcados[i] = 0;
            }
        }

        for (int i = valork-1; i < TAM; i++) {
            if (numerosNaoMarcados[i] != 0) {
                valork = numerosNaoMarcados[i];
                break;
            }
        }

    } while((valork * valork) < n);
}

int main() {

    pthread_t thread_id; 
    printf("Before Thread\n"); 
    pthread_create(&thread_id, NULL, crivo, NULL); 
    pthread_join(thread_id, NULL); 
    printf("After Thread\n"); 

    printf("Numeros primos: ");
    for(int i = 0; i < TAM; i++) {
        if(numerosNaoMarcados[i] != 0)
            printf("%d ", numerosNaoMarcados[i]);
    }
    printf("\n");

    return 0;
}