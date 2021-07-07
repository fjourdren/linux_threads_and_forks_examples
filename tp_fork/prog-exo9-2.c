#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NB_PROCESSUS 5

int main()
{

    pid_t pidfilsArray[NB_PROCESSUS];
    pid_t pidfils = -1;

    for(int i = 0; i < NB_PROCESSUS;  i = i + 1)
    {
        pidfils = fork();
        
        if(pidfils == -1) 
        {
            printf("Erreur de fork\n");
            return EXIT_FAILURE;
        }

        pidfilsArray[i] = pidfils;

        // fils
        if(pidfils == 0)
        {
            sleep(3);
            printf("Fils finished\n");
            return EXIT_SUCCESS;
        }

    }

    if(pidfils != 0) {
        for(int i = 0; i < NB_PROCESSUS; i = i + 1)
        {
            waitpid(pidfilsArray[i], NULL, 0);
            printf("Fils killed %d\n", i);
        }

         printf("End\n");
        return EXIT_SUCCESS;
    }
    
}