# ASSIGNMENT01
__________________________________________________________________________________________
## TL;DR version
* Compile and run each part as specified by the instructions.  <UNIX command> may be replaced by ls, ps, ls -a, etc.

To run part 1.a of assignment 1:
```
~$ gcc -o pre pre.c -std=c99
```
```
~$ ./pre
```
To run part 1.b of assignment 1: First ensure pre.c noted above is compiled
```
~$ gcc -o sort sort.c -std=c99
```
```
~$ ./pre | ./sort
```
To run part 2 of assignment 1: First ensure executables are in place for pre.c and sort.c

Compile Part 2 (child_to_parent.c)
```
~$ gcc -o child_to_parent child_to_parent.c -std=c99
```
Execute child_to_parent
```
~$ ./child_to_parent
```
To run part 3 of assignment 1:
```
~$ gcc -o fork fork_a_child.c -std=c99
```
```
~$ ./fork <UNIX command>  Possible UNIX commands: ps, ls -a
```
______________________________________________________________________________________

### Part 1: Write small C programs
* A) The first program "pre.c" should read in a list of U.S. states and their populations.  You can google to find the information. To be simple, you can use the abbreviation for each state.  We assume there are at most 10 states in the list.  Enter the inputs through the keyboard and display the output on the screen.  The input ends when an EOF (CTRL-D) is encountered.  The output of the program should display the states whose population is above 10 million.

To run part 1.a of assignment 1:
```
~$ gcc pre.c -std=c99
```
```
~$ ./a.out
```
To run part 1.b of assignment 1: first ensure pre.c noted above is compiled
```
~$ gcc -o sort sort.c -std=c99
```
```
~$ ./pre | ./sort
```

* B) The second program "sort.c" reads in a list of state abbreviations from stdin and displays them in alphabetical order on the screen.  Assume there are no more than 10 states and the sequence is read until you press CTRL-D which generates an EOF.

To run part 1.b of assignment 1:
```
~$ gcc -o pre pre.c && gcc -o sort sort.c
```
```
~$ ./pre | ./sort
```

### Part 2:
* Write a c program to set up a child-TO-parent pipe; the child should 'exec' to perform the "pre" process from the above and its output should be connected to the pipe connected to the parent, which should 'exec' to perform the "sort" process from the above.

To run part 2 of assignment 1:
First ensure executables are in place for pre.c and sort.c
```
~$ ./pre | ./sort
```
Compile Part 2 (child_to_parent.c)
```
~$ gcc -o child_to_parent child_to_parent.c
```
Execute child_to_parent
```
~$ ./child_to_parent
```

### Part 3:
* Write a program to take a UNIX command from the command line and fork() a child to execute it.  The command can be a simple command like $ls or $ps, or it can be a command with options such as $ls -t -l.  Use argc and argv[] in the main function to pass parameters.  When the child process is executing the command, the parent process simply waits for the termination of the child process.  The process id of the parent and the child should be printed out using getpid() and getppid() functions.

To run part 3 of assignment 1:
```
~$ gcc -o fork fork_a_child.c
```
```
~$ ./fork <UNIX command>  Possible UNIX commands: ps, ls -a
```
