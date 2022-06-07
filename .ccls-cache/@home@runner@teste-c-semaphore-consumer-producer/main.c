#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>

#define Letras 6	//itens Quatidade
#define BufferSize 6	//buffers

sem_t empty;
sem_t full;
int entrada = 0, saida = 0, buffer[BufferSize];
//pthread_mutex_t mutex;

void *produtor1(void *prod1){
    int item;
	sem_wait(&empty);
	//pthread_mutex_lock(&mutex);
    for(int i = 0; i < Letras;i++){
        item = '0'+i;
        buffer[entrada] = item;
        printf("Producer 1 %i: Insert Item %i at %i\n", *((int *)prod1), buffer[entrada],entrada);
		//sleep(1);
        entrada = (entrada+1)%BufferSize;
        
    }
	sem_post(&full);
	//pthread_mutex_unlock(&mutex);
}

void *consumidor1(void *cons1){
	
	sem_wait(&full);
	//pthread_mutex_lock(&mutex);
	printf("Buffer liberador \n");
	for(int i = 0; i < Letras; ++i){
        int item = buffer[saida];
        printf("Consumidor 1 %i: Remove Item %i from %d\n", *((int *)cons1), item, saida);
        saida = (saida + 1)%BufferSize;
    }
	sem_post(&empty);
	//pthread_mutex_unlock(&mutex);
}

void *produtor2(void *prod2){
    int item;
	sem_wait(&empty);
	//pthread_mutex_lock(&mutex);
    for(int i = 0; i < Letras;i++){
        item = '0'+i;
        buffer[entrada] = item;
        printf("Producer 2 %i: Insert Item %i at %i\n", *((int *)prod2), buffer[entrada],entrada);
		//sleep(1);
        entrada = (entrada+1)%BufferSize;
        
    }
	sem_post(&full);
	//pthread_mutex_unlock(&mutex);
}

void *consumidor2(void *cons2){
	
	sem_wait(&full);
	//pthread_mutex_lock(&mutex);
	printf("Buffer liberador \n");
	for(int i = 0; i < Letras; ++i){
        int item = buffer[saida];
        printf("Consumidor 2 %i: Remove Item %i from %d\n", *((int *)cons2), item, saida);
        saida = (saida + 1)%BufferSize;
    }
	sem_post(&empty);
	//pthread_mutex_unlock(&mutex);
}

int main(){
    pthread_t pro1, con1, pro2, con2;
	//pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, BufferSize);
    sem_init(&full, 0, 0);

    pthread_create(&pro1, NULL, (void *)produtor1, (void *)&pro1);
    pthread_create(&con1, NULL, (void *)consumidor1, (void *)&con1);
	pthread_create(&pro2, NULL, (void *)produtor2, (void *)&pro2);
	pthread_create(&con2, NULL, (void *)consumidor2, (void *)&con2);

    pthread_join(pro1, NULL);
    pthread_join(con1, NULL);
	pthread_join(pro2, NULL);
	pthread_join(con2, NULL);

    //pthread_mutex_destroy(&mutex);
	sem_destroy(&empty);
    sem_destroy(&full);

    printf("\n Main done \n");
    return 0;

}
