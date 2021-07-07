#include <unistd.h>
#include <stdio.h>

int main()
{
    char pid[10];
    snprintf(pid, 10, "%i", getppid());

    char * args[2];

    args[0] = "-h";
    args[1] = pid;
    args[2] = NULL;

    execv("/usr/bin/pstree", args);
    return 0;
}
