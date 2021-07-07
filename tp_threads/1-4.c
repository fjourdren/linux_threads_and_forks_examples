#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_int {
  long int N;
  int cpt;
} s_int;

typedef struct s_pointer {
  long int N;
  int * ptCpt;
} s_pointer;

void *thread_incrementeur1(void *arg);
void *thread_afficheur1(void *arg);

void *thread_incrementeur2(void *arg); // arg is a pointeur to a s_int
void *thread_afficheur2(void *arg); // arg is a pointeur to a s_int

void *thread_incrementeur3(void *arg); // arg is a pointeur to a s_pointer
void *thread_afficheur3(void *arg); // arg is a pointeur to a s_pointer

int compteur1 = 0;

int main(void)
{
	long int N = 5L;
	
	int compteur2 = 0;
	int * compteur3 = (int*) malloc(sizeof(int));

	s_int s2;
	s2.N = N;
	s2.cpt = compteur2;
	
	s_pointer s3;
	s3.N = N;
	s3.ptCpt = compteur3;
	
	s_pointer s4;
	s4.N = N;
	s4.ptCpt = &compteur2;

	/* Expe 1 */
	printf("** Expe 1 **\n");
	pthread_t thr1, thr2;
	if (pthread_create(&thr1, NULL, thread_incrementeur1, (void *)N) != 0) {
		fprintf(stderr, "Erreur dans pthread_create\n");
		exit(EXIT_FAILURE);
	}
	if (pthread_create(&thr2, NULL, thread_afficheur1, (void *)N) != 0) {
		fprintf(stderr, "Erreur dans pthread_create\n");
		exit(EXIT_FAILURE);
	}

	if (pthread_join(thr1, NULL)) {
		perror("pthread_join");
	}
	if (pthread_join(thr2, NULL)) {
		perror("pthread_join");
	}
	printf("** Expe 1 -- FIN **\n");
	/* Fin expe 1*/

	/* Expe 2 */
	printf("** Expe 2 **\n");
	pthread_t thr3, thr4;
	if (pthread_create(&thr3, NULL, thread_incrementeur2, (void *)&s2) != 0) {
		fprintf(stderr, "Erreur dans pthread_create\n");
		exit(EXIT_FAILURE);
	}
	if (pthread_create(&thr4, NULL, thread_afficheur2, (void *)&s2) != 0) {
		fprintf(stderr, "Erreur dans pthread_create\n");
		exit(EXIT_FAILURE);
	}

	if (pthread_join(thr3, NULL)) {
		perror("pthread_join");
	}
	if (pthread_join(thr4, NULL)) {
		perror("pthread_join");
	}
	printf("** Expe 2 -- FIN **\n");
	/* Fin expe 2*/

	/* Expe 3 */
	printf("** Expe 2 **\n");
	if (pthread_create(&thr1, NULL, thread_incrementeur3, (void *)&s3) != 0) {
		fprintf(stderr, "Erreur dans pthread_create\n");
		exit(EXIT_FAILURE);
	}
	if (pthread_create(&thr2, NULL, thread_afficheur3, (void *)&s3) != 0) {
		fprintf(stderr, "Erreur dans pthread_create\n");
		exit(EXIT_FAILURE);
	}

	if (pthread_join(thr1, NULL)) {
		perror("pthread_join");
	}
	if (pthread_join(thr2, NULL)) {
		perror("pthread_join");
	}
	printf("** Expe 3 -- FIN **\n");
	/* Fin expe 3*/

	/* Expe 4 */
	printf("** Expe 4 **\n");
	if (pthread_create(&thr1, NULL, thread_incrementeur3, (void *)&s4) != 0) {
		fprintf(stderr, "Erreur dans pthread_create\n");
		exit(EXIT_FAILURE);
	}
	if (pthread_create(&thr2, NULL, thread_afficheur3, (void *)&s4) != 0) {
		fprintf(stderr, "Erreur dans pthread_create\n");
		exit(EXIT_FAILURE);
	}

	if (pthread_join(thr1, NULL)) {
		perror("pthread_join");
	}
	if (pthread_join(thr2, NULL)) {
		perror("pthread_join");
	}
	printf("** Expe 4 -- FIN **\n");
	/* Fin expe 4*/
	
	free(compteur3);
	exit(EXIT_SUCCESS);
}

void *thread_incrementeur1(void *arg)
{
	long int N = (long int)arg;
	for(int i = 0; i < N; ++i){
	  sleep(1);
	  compteur1 += 1;
	}

	pthread_exit(NULL);
}

void *thread_afficheur1(void *arg)
{
	long int N = (long int)arg;
	for(int i = 0; i < N; i += 2){
	  sleep(2);
	  printf("\tcpt = %d\n", compteur1);
	}

	pthread_exit(NULL);
}

void *thread_incrementeur2(void *arg)
{
	s_int * s = (s_int *)arg;
	printf("N = %ld\n", s->N);
	for(int i = 0; i < s->N; ++i){
	  sleep(1);
	  s->cpt += 1;
	}

	pthread_exit(NULL);
}

void *thread_afficheur2(void *arg)
{
	s_int * s = (s_int *)arg;
	for(int i = 0; i < s->N; i += 2){
	  sleep(2);
	  printf("\tcpt = %d\n", s->cpt);
	}

	pthread_exit(NULL);
}


void *thread_incrementeur3(void *arg)
{
	s_pointer * s = (s_pointer *)arg;
	for(int i = 0; i < s->N; ++i){
	  sleep(1);
	  *(s->ptCpt) += 1;
	}

	pthread_exit(NULL);
}

void *thread_afficheur3(void *arg)
{
	s_pointer * s = (s_pointer *)arg;
	for(int i = 0; i < s->N; i += 2){
	  sleep(2);
	  printf("\tcpt = %d\n", *(s->ptCpt));
	}

	pthread_exit(NULL);
}
