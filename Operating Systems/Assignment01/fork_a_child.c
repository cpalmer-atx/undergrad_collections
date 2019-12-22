#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

void output_after_wait();

int main(int argc, char const *argv[]) {
	int pid;
	int status;
    
    switch (pid = fork())
    {
    case -1:        // An error has occured
        printf("Fork failed.\n");
		exit(1);
        break;
    case 0:         // Child Process
        printf("~$%s command executed.\n", argv[1]);
		printf("~$%s command results:\n", argv[1]);
        system(argv[1]);
		printf("End of child process.\n");
        break;
    default:        // Parent Process
        wait(&status);
        output_after_wait();
        break;
    }
	return 0;
}

void output_after_wait() {
    printf("------------------------------------------------\n");
    printf("End of parent process.\n");
	printf("Child pid: %d\nParent pid: %d\n", getpid(), getppid());
}