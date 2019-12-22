#include <stdio.h>
#include <sys/types.h>		// for use of open()
#include <sys/stat.h>		// for use of open()
#include <fcntl.h>			// for open() file access modes (i.e. O_RDONLY, O_WRONLY, etc)
#include <stdlib.h>
#include <string.h>
#include <unistd.h>			// Imports POSIX API
#include <sys/wait.h>


int main()
{
	char *in_path, *out_path, *argv[20], buf[80], n, *p;
	int m, status, inword, continu;

	int j = 0;					// index variable for pipe mgmt loop
	int index = 0;				// index variable for redirection mgmt loop
	int pipe_count = 0;			// a variable to keep track of pipes
	int redirect[20];			// a buffer for redirects in argv[]
	int in_path_flag = 0;		// signaler for in_path redirects
	int out_path_flag = 0;		// signaler for out_path redirects

	pid_t pid;
	int l_fd[2];				//  left pipe
	int r_fd[2];				// right pipe
	int in_fd = 0;				//  input file descriptor
	int out_fd = 0;				// output file descriptor
	int clear_cmds = 0;			// index variable to clear existing commands for next user input

	while(1) {

		inword = 0;
		p = buf;
		m = 0;
		continu= 0;
		in_path_flag = 0;
		out_path_flag = 0;
		index = 0;
		j = 0;
		in_fd = 0;
		out_fd = 0;
		clear_cmds = 0;
		
		printf( "\nshhh> ");

		/****************** Provided code for parsing ********************/

		while ( (n = getchar()) != '\n' || continu ) {

			if ( n ==  ' ' ) {
			    if ( inword ) {
					inword = 0;
					*p++ = 0;
			    }
			}
			else if ( n == '\n' ) continu = 0;
			else if ( n == '\\' && !inword ) continu = 1;
			else {

			    if ( !inword ) {
					inword = 1;
					argv[m++] = p;
					*p++ = n;
			    }
			    else
					*p++ = n;
			}
		}
		*p++ = 0;
		argv[m] = 0;

		if ( strcmp(argv[0],"exit") == 0 ) exit (0);

		/************** Parsing complete, argv[] populated ***************/


		/******************** Redirection management *********************/

		// argv[] is scanned for redirect commands.  If a redirect is found,
		// it is buffered in redirect[] to recall later.

		while (argv[index] != 0) {
			if (strcmp(argv[index], "|") == 0) {
				argv[index] = 0;
				redirect[pipe_count + 1] = index + 1;
				++pipe_count;
			}
			else if (strcmp(argv[index], "<") == 0) {
				in_path = strdup(argv[index + 1]);
				argv[index] = 0;
				in_path_flag = 1;
			}
			else if (strcmp(argv[index], ">") == 0) {
				out_path = strdup(argv[index + 1]);
				argv[index] = 0;
				out_path_flag = 1;
			}
			else {
				redirect[index] = index;
			}
			++index;
		}

		/***************** End redirection management ********************/


		/******************* Begin pipe management ***********************/

		for (j = 0; j <= pipe_count; ++j) {

			if (pipe_count > 0 && j != pipe_count)	{ pipe(r_fd); }

			switch (pid = fork()) {
				case -1:
					printf("Failed to fork.\n");
					exit(1);
					break;
				case  0:
					if ( (in_path_flag == 1) && (j == 0) ) {
						in_fd = open(in_path, O_RDONLY, 0400);
						if (in_fd == -1) {
							printf("ERROR: infile failed to open. exiting\n");
							return(EXIT_FAILURE);
						}
						close(0);
						dup(in_fd);
						close(in_fd);
					}
					if ( (out_path_flag == 1) && (j == pipe_count) ) {
						out_fd = creat(out_path, 0700);
						if (out_fd < 0) {
							printf("ERROR: outfile failed to open. exiting\n");
							return(EXIT_FAILURE);
						}
						close(1);
						dup(out_fd);
						close(out_fd);
					}
					if (pipe_count > 0) {
						// Handle first child process
						if (j == 0) {
							close(1);
							dup(r_fd[1]);
							close(r_fd[1]);
							close(r_fd[0]);
						}
						// Handle middle child process
						else if (j < pipe_count) {
							close(0);
							dup(l_fd[0]);
							close(l_fd[0]);
							close(l_fd[1]);
							close(1);
							dup(r_fd[1]);
							close(r_fd[0]);
							close(r_fd[1]);
						}
						// Handle last child process
						else {
							close(0);
							dup(l_fd[0]);
							close(l_fd[0]);
							close(l_fd[1]);
						}
					}
					execvp(argv[redirect[j]], &argv[redirect[j]]);
					perror("Command failed to execute.\n");
					break;
				default:
					if (j > 0) {
						close(l_fd[0]);
						close(l_fd[1]);
					}
					l_fd[0] = r_fd[0];
					l_fd[1] = r_fd[1];
					wait(&status);
					break;
			}
		}
		for (clear_cmds = 0; clear_cmds < 80; ++clear_cmds)  { 
			buf[clear_cmds] = 0;
			if (clear_cmds < 20) {
				argv[clear_cmds] = 0;
				redirect[clear_cmds] = 0;
			}
			if (clear_cmds < 2) {
				l_fd[clear_cmds] = 0;
				r_fd[clear_cmds] = 0;
			}
		}

		/******************** End pipe management ************************/
	}
}
