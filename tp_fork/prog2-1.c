#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    // init
    pid_t pid_fils = -1;

    // fork
    pid_fils = fork();

    // gestion erreur
    if(pid_fils == -1)
    {
        perror("Echec du fork\n");
        return (EXIT_FAILURE);
    }


    if(pid_fils == 0)
    {
        sleep(2);
        printf("Monsieur le Président, je vous fais une lettre.\n");
    }
    else
    {
        wait(NULL);
        printf("que vous lirez peut-être si vous avez le temps\n");
        return EXIT_SUCCESS;
    }

    return (EXIT_SUCCESS);
}