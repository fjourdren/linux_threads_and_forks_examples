#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *code_thread1(void *arg);
void *code_thread2(void *arg);

int main(void) {
    pthread_t thr1, thr2;

    if(pthread_create(&thr1, NULL, code_thread1, (void*)1L)!=0) {
        fprintf(stderr, "Erreur dans pthread_create\n");
        exit(EXIT_FAILURE);
    }

    if(pthread_create(&thr2, NULL, code_thread2, (void*)2L)!=0) {
        fprintf(stderr, "Erreur dans pthread_create\n");
        exit(EXIT_FAILURE);
    }


    fprintf(stderr, "Thread principal: Affichage 1/5\n");
    sleep(1);
    fprintf(stderr, "Thread principal: Affichage 2/5\n");
    sleep(1);
    fprintf(stderr, "Thread principal: Affichage 3/5\n");
    sleep(1);
    fprintf(stderr, "Thread principal: Affichage 4/5\n");
    sleep(1);
    fprintf(stderr, "Thread principal: Affichage 5/5\n");
    sleep(1);


    system("ps -m");

    pthread_join(thr1, NULL);
    pthread_join(thr2, NULL);

    exit(EXIT_SUCCESS);
}

void *code_thread1(void *arg) {
    long int num = (long int) arg;
    fprintf(stderr, "Thead numero %ld : Affichage 1/6\n", num);
    sleep(1);
    fprintf(stderr, "Thead numero %ld : Affichage 2/6\n", num);
    sleep(1);
    fprintf(stderr, "Thead numero %ld : Affichage 3/6\n", num);
    sleep(1);
    fprintf(stderr, "Thead numero %ld : Affichage 4/6\n", num);
    sleep(1);
    fprintf(stderr, "Thead numero %ld : Affichage 5/6\n", num);
    sleep(1);
    fprintf(stderr, "Thead numero %ld : Affichage 6/6\n", num);
    sleep(1);

    return NULL;
}

void *code_thread2(void *arg) {
    long int num = (long int) arg;
    fprintf(stderr, "Thread numero %ld : Affichage 1/2\n", num);
    sleep(1);
    fprintf(stderr, "Thread numero %ld : Affichage 2/2\n", num);
    sleep(1);

    return NULL;
}