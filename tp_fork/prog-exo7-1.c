#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{

    pid_t pidfils = -1;
    pidfils = fork();

    if(pidfils == -1) 
    {
        printf("Erreur de fork");
        return EXIT_FAILURE;
    }


    // fils
    if(pidfils == 0)
    {
        printf("Fils début\n");
        sleep(20);
        printf("Fils fin\n");
        return EXIT_SUCCESS;
    }
    // père
    else
    {
        printf("Père début\n");
        wait(&pidfils);
        printf("Père fin\n");
        return EXIT_SUCCESS; 
    }
}