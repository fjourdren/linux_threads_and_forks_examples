#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/types.h>

int main()
{
    // récupère le retour du fork
    pid_t pid_fils = -1;
    pid_fils = fork();


    // gestion erreur
    if(pid_fils == -1)
    {
        perror("Echec du fork\n");
        return (EXIT_FAILURE);
    }


    if(pid_fils == 0)
    {
        printf("(%d) Je suis le fils de %d.\n", getpid(), getppid());
    }

    printf("(%d) All you need is love.\n", getpid());
    sleep(15);
    return (EXIT_SUCCESS);
}