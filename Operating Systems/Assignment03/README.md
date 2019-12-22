# ASSIGNMENT03 - Specifications
__________________________________________________________________________________________
Simulate the concurrent execution of two threads using a single program:
Thread A: prints five subsequent lines of letter A on the printer and keeps looping (about 10 times).
Thread B: prints five subsequent lines of letter B on the printer and keeps looping (about 10 times).

### Part A:
Do NOT use any algorithm for mutual exclusion and show the printout.

### Part B:
Write the program from Part A again, this time considering mutual exclusion.

### Running the programs:

```
~$ gcc -pthread -o partA partA.c
```
```
~$ gcc -pthread -o partB partB.c
``` 
```
~$ ./partA
``` 
```
~$ ./partB
``` 
