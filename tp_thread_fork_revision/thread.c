#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct max {
    int val;
    size_t id;
} max_t;

typedef struct thread_param {
    int* tab;
    size_t nbElem;
    size_t offset;
    max_t* res;
    pthread_mutex_t *mutex;
} thread_param_t;

unsigned int NB_THREADS = 3;

size_t max_tableau(int *t, size_t size) {
    size_t i = 0;
    size_t res = 0;

    while(!(i==size)) {
        if(t[res] < t[i]) {
            res = i;
        }

        ++i;
    }

    return res;
}

void *function_thread(void* param) {
    thread_param_t* args = (thread_param_t*) param;

    size_t maxIndexSousTab = max_tableau(args->tab, args->nbElem);
    
    if(args->res->val < args->tab[maxIndexSousTab]) {
        pthread_mutex_lock(args->mutex);
        args->res->val = args->tab[maxIndexSousTab];
        args->res->id = maxIndexSousTab + args->offset;
        pthread_mutex_unlock(args->mutex);
    }
    return NULL;
}

int main() {
    pthread_t thrArray[NB_THREADS];
    size_t nbE = 15;
    int t[] = {0,1,4,2,4,6,7,56,5,4,100,7,9,20,18};

    size_t sizeSousTableau = (size_t) nbE / NB_THREADS;
    max_t* maxRes = (max_t*) malloc(sizeof(max_t));
    pthread_mutex_t mutexToEnter = PTHREAD_MUTEX_INITIALIZER;

    for(size_t i = 0; i < NB_THREADS; ++i) {
        thread_param_t* thread_param = (thread_param_t*) malloc(sizeof(thread_param_t));
        
        thread_param->tab = &t[i * sizeSousTableau];
        thread_param->offset = i * sizeSousTableau;
        thread_param->res = maxRes;
        thread_param->mutex = &mutexToEnter;
        if(i != NB_THREADS - 1) {
            thread_param->nbElem = sizeSousTableau;
        } else {
            thread_param->nbElem = nbE - i * sizeSousTableau;
        }
        

        if (pthread_create(&(thrArray[i]), NULL, function_thread, (void *)thread_param) != 0) {
            fprintf(stderr, "Erreur dans pthread_create\n");
            exit(EXIT_FAILURE);
        }
    }

    for(size_t i = 0; i < NB_THREADS; ++i){
        if (pthread_join(thrArray[i], NULL)) {
            perror("pthread_join\n");
        }

        pthread_detach(thrArray[i]);
    }

    printf("Résultat : %i à la position : %li\n", maxRes->val, maxRes->id);
}