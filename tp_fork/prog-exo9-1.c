#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int levelParente = 0;
    pid_t fils = 0;

    while(levelParente <= 3 && fils == 0)
    {
        fils = fork();

        if(fils == -1)
        {
            printf("Erreur de fork\n");
            return EXIT_FAILURE;
        }

        if(fils != 0) {
            printf("Fils niveau %d créée\n", levelParente);
        }
        
        levelParente = levelParente + 1;
    }

    if(fils != 0)
    {
        waitpid(fils, NULL, 0);
    }
    
    printf("End\n");
    return EXIT_SUCCESS;
}