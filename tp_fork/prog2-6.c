#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    pid_t pid_fils = -1;
    pid_fils = fork();

    if(pid_fils == -1) {
        perror("Echec de fork\n");
        return EXIT_FAILURE;
    }

    if(pid_fils == 0) {
        for(int i = 0; i < 10; i++) {
            printf("(fils %d) .. mon père est %d\n", getpid(), getppid());
            sleep(2);
        }

        printf("(fils %d) j'ai terminé.\n", getpid());
        return EXIT_SUCCESS;
    } else {
        for(int i = 0; i<5; i++) {
            printf("(père %d) .. \n", getpid());
            sleep(2);
        }


        wait(&pid_fils);

        printf("(père %d) J'ai terminé. \n", getpid());
        return EXIT_FAILURE;
    }
}