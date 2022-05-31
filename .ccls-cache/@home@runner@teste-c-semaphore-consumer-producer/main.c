#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>

#define Letras 10			//itens Quatidade
#define BufferSize 5		//buffers

sem_t empty;
sem_t full;
int entrada = 0, saida = 0, buffer[BufferSize];
//pthread_mutex_t mutex;

void *produtor(void *prod){
    int item;
	sem_wait(&empty);
    for(int i = 0; i < Letras;i++){
        item = 'a'+i;
		//sleep(1);
        //pthread_mutex_lock(&mutex);
        buffer[entrada] = item;
        printf("Producer %i: Insert Item %c at %i\n", *((int *)prod), buffer[entrada],entrada);
		//sleep(1);
        entrada = (entrada+1)%BufferSize;
        //pthread_mutex_unlock(&mutex);
        
    }
	sem_post(&full);
}

void *consumidor(void *cons){
	
	sem_wait(&full);
	printf("Buffer liberador");
	for(int i = 0; i < Letras; ++i){
        
        //pthread_mutex_lock(&mutex);
        int item = buffer[saida];
        printf("Consumidor %i: Remove Item %c from %d\n", *((int *)cons), item, saida);
        saida = (saida + 1)%BufferSize;
        //pthread_mutex_unlock(&mutex);
    }
	sem_post(&empty);
}


int main(){
    pthread_t pro, con;
    //pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, BufferSize);
    sem_init(&full, 0, 0);

    pthread_create(&pro, NULL, (void *)produtor, (void *)&pro);
    pthread_create(&con, NULL, (void *)consumidor, (void *)&con);

    pthread_join(pro, NULL);
    pthread_join(con, NULL);

   // pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    printf("\n Main done \n");
    return 0;

}