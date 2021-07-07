#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NB_THREADS 10
#define MAX_CPT 50

/* Horribles variables globales */
int mymutex = 0;
int cpt = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *thread_cpt(void *arg);

int main(void)
{
  pthread_t thrArray[NB_THREADS];
  for(long int i =0; i < NB_THREADS; ++i){
    if (pthread_create(&(thrArray[i]), NULL, thread_cpt, (void *)i) != 0) {
      fprintf(stderr, "Erreur dans pthread_create\n");
      exit(EXIT_FAILURE);
    }
  }

  for(long int i =0; i < NB_THREADS; ++i){
    if (pthread_join(thrArray[i], NULL)) {
      perror("pthread_join");
    }
  }

  exit(EXIT_SUCCESS);
}

void *thread_cpt(void *arg)
{
  long int tId = (long int)arg;

  while(cpt < MAX_CPT){
    pthread_mutex_lock(&mutex);
    cpt = cpt + 1;

    printf("Th %ld : cpt = %d\n",tId,cpt);
    pthread_mutex_unlock(&mutex);
    

    sleep(1); // forcer la commutation vers un autre thread
  }
  pthread_exit(NULL);
}
