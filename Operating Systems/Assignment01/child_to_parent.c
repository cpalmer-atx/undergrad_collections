#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>         // For close, dup, dup2, execv, fork, pipe
#include <sys/types.h>      // For use of pid_t

int main(int argc, char* const argv[]) {
    int p[2];
    pipe(p);        // The pipe:  p[1] --> [||||||||] --> p[0]
    pid_t pid;

    switch (pid = fork())
    {
    case -1:    // An error has occured
        printf("Fork failed.\n");
        exit(2);
        break;
    case 0:     // Read in to the pipe
        close(p[0]);
        dup2(p[1], 1);
        close(p[1]);

        execv("pre", argv);
        exit(1);
        break;
    default:    // Write out of the pipe
        close(p[1]);
        dup2(p[0], 0);
        close(p[0]);

        execv("sort", argv);
        perror("\nexecl() failed to sort.\n");
        break;
    }
    return 0;
}