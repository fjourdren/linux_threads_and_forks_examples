#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    // init
    pid_t pid_fils1 = -1;
    pid_t pid_fils2 = -1;

    const char *royaume = "Aucun";

    royaume = "Carmélide";

    printf("(Léodagan, PID: %d, PPID: %d) voici mon royaume: %s.\n", getpid(), getppid(), royaume);
    
    
    // fork
    pid_fils1 = fork();

    // gestion erreur
    if(pid_fils1 == -1)
    {
        perror("Echec du fork\n");
        return (EXIT_FAILURE);
    }


    if(pid_fils1 != 0)
    {
        pid_fils2 = fork();
        if(pid_fils2 == -1)
        {
            perror("Echec du fork\n");
            return (EXIT_FAILURE);
        }

        if(pid_fils2 == 0)
        {
            printf("(Yvain, PID: %d, PPID: %d) voici mon royaume: %s.\n", getpid(), getppid(), royaume);
        }
    }
    else
    {
        printf("(Guenièvre, PID: %d, PPID: %d) voici mon royaume: %s.\n", getpid(), getppid(), royaume);
        royaume = "Logres";

        printf("(Guenièvre, PID: %d, PPID: %d) voici mon royaume: %s.\n", getpid(), getppid(), royaume);
    }

    wait(NULL);
    wait(NULL);
    return (EXIT_SUCCESS);
}