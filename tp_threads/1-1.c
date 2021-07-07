#include <unistd.h>
#include <stdio.h>

int main()
{
    char pid[10];
    snprintf(pid, 10, "%i", getppid());

    int code_error = execl("/usr/bin/pstree", "pstree", "-h", pid, NULL);
    printf("Problème: %i\n", code_error);
    return 0;
}
