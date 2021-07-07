#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    int i;

    for(i = 1; i < 30; i++) {
        printf("(%d) %d km à pied, ca use, %d km ca use les souliers. \n", getpid(), i, i);
        sleep(1);
    }

    return (EXIT_SUCCESS);
}