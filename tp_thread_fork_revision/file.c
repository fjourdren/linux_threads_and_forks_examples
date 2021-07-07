#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    int p[2];
    char buf[20];
    int status;
    pid_t pid;

    pipe(p); // création du pipe

    pid = fork();
    if (pid) { /* pere */
        close (p[0]);   //on ferme le coté lecture du pipe
        write (p[1], "bonjour", 8);     // on écrit dans le pipe

        waitpid(pid, &status, 0); // on attend le fils et on vérifie si il y a une erreur

        if(status == EXIT_FAILURE) {
            fprintf(stderr,"Error dans le fils");
            exit(EXIT_FAILURE);
        }
    } else if(pid == 0) { /* fils */
        close (p[1]);   // on ferme l'écriture
        read (p[0], buf, 8);    // on lit le pipe
        printf ("j'ai recu : '%s'\n", buf);
    } else {
        fprintf(stderr,"Error fork");
        exit(EXIT_FAILURE);
    }
}