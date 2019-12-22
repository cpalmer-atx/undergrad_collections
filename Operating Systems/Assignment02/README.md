# ASSIGNMENT02 - Specifications
__________________________________________________________________________________________
This lab seeks to demonstrate a basic understanding of pipe and redirection management through the implementation of a simple shell program.  The provided lab2.c file can already parse user input into a defined argv[] array and assumes all input is correct.  The primary objectives are:
1. Define redirection and pipe commands (">", "<", "|").
2. Manage redirection and pipes using what is known about process management and the piping process.
A more detailed explaination of the lab objectives is provided at the end of this specifications section.

To test this lab, source code and executables from lab 1 are provided.  Sample commands in the objectives section below should be sufficient for testing purposes.  To launch this program:

```
~$ gcc -o shhh lab2.c
```
```
~$ ./shhh
``` 

### A special note on pre.c and sort.c executables:
Although executables are provided for simplicity, it should be noted that successful compilation of these programs on the Texas State University servers and other various linux machines require the specification of gcc version c99.  You can do this by adding the std=c99 tag:

```
~$ gcc -o pre pre.c -std=c99
```
```
~$ gcc -o sort sort.c -std=c99
```
### DO NOT SPECIFY std=c99 FOR LAB2.C!  The resulting executable will not recognize redirects.

# ASSIGNMENT02 - Objectives (as provided in class)
__________________________________________________________________________________________
## Write a small shell - called shhh - that has the following capabilities:
* Can execute a command with the accompanying arguments.
* Recognize multiple pipe requests and handle them.
* Recognize redirection requests and handle them.
* Type "exit" to quit the shhh shell.

### Sample commands:

```
shhh>ls
```
```
shhh>ls -t -al
```
```
shhh>cat file.txt   (file.txt is an existing file)
```
```
shhh>ls -al > output.txt
```
Be sure to open output.txt to see if the content is correct or not


```
shhh> ls | more | wc
```

```
shhh>./pre < input.txt | ./sort > output.txt
```
pre and sort are executables from ASSIGNMENT01. 'input.txt' is the file that provides the input and 'output.txt' is the output file.
```
shhh>exit
```

The shell shhh should always wait for ALL the commands to finish. The topology of the forked processes should be linear children; e.g. the shell should have as many children as there are processes needed - with pipes connecting adjacent children.  You may assume that any redirection in the command is specified like the third example above.  E.g. "redirection in" ( < ) is always specified before the first pipe appears and "redirection out" ( > ) is always after the last pipe specified.  To make life easier for you, you may assume that only commands with correct syntax are typed in.  In other words don't worry about errors in the formation of the commands.  The partial program is available in TRACS, lab2.c. The command parsing part is already done in the program.  On your part, you need to implement the above functions.
