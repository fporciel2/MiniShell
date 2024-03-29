# MiniShell

    MiniShell is a simple shell for Debian GNU/Linux.
    Copyright (C) 2024  Federico Porciello

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

## Introduction

MiniShell is a product of objectification of labor. The shell, in its essence, is a mediator between the user and the complexity of the operating system, much like language is a mediator of reality. Indeed, it 
involves the construction of a user interface *and* an object language: as an object language, it is the objectification of the formal system of human-operating system interaction; as a user interface, it is the 
objectification of the human custom in this interaction.
Minishell applies computer science principles by founding on how software interfaces with hardware, how processes are managed, and how data flows through file descriptors. These elements are conceptualized through 
breaking each command and process into logical units that perform specific functions.
The operation of file descriptors and processes involves underlying physical principles of computing, including electricity flow through circuits and data representation through physical states (e.g., voltage 
levels). The manipulation of these descriptors in Minishell is a direct interaction with the physical properties of the computer along multiple levels of abstraction.
From a metaphysical perspective, MiniShell acts as a microcosm of order and control within the chaotic potential of the operating system. It reflects the philosophical quest for understanding and shaping the 
world (in this case, the operating system) through a structured framework of commands and processes. This mediation process is strictly related with [synchronization problems](https://github.com/fporciel2/Philosophers).

File descriptors are integral to Unix and Unix-like operating systems, serving as abstract indicators for accessing files and other I/O resources, including pipes and sockets. In the context of MiniShell, file 
descriptors allow for redirection, piping, and control of input and output streams, which are critical for the shell's operation. The manipulation of these descriptors must be carefully managed, especially in 
environments where multiple processes or threads access shared resources, to avoid conflicts, ensure data integrity, and maintain system stability.
The dining philosophers problem, conceived by Edsger W. Dijkstra, is a classic illustration of synchronization issues in computing. It involves a scenario where a certain number of philosophers sit around a table, 
with a fork between each pair, and each philosopher alternately thinks and eats. To eat, a philosopher needs both forks on either side of them. The problem illustrates the challenges of resource allocation and 
deadlock prevention in concurrent programming.
The connection between shell operations on file descriptors and the dining philosophers problem lies in the shared underlying theme of resource management and synchronization in environments where multiple 
entities (processes, threads, or philosophers) require access to shared resources (file descriptors, forks). Just as philosophers need access to forks to eat, multiple processes managed by a shell may need access 
to the same file descriptors for I/O operations. Allocating these resources without causing conflict or starvation (where a process is perpetually denied access to a resource) mirrors the challenge of ensuring 
each philosopher gets a chance to eat. In the dining philosophers problem, a naive allocation strategy could lead to a deadlock, where each philosopher holds one fork, and no one can eat. Similarly, improper 
management of file descriptors, especially when processes are interdependent (e.g., through piping), can lead to deadlocks in a system, where processes are waiting on each other to release resources.
Solutions to the dining philosophers problem often involve sophisticated synchronization mechanisms (e.g., semaphores, monitors) to avoid deadlock and ensure fair resource allocation. In shell operations, similar 
mechanisms (locking, careful order of operations) are required to manage file descriptors among processes, ensuring that data flows smoothly without bottlenecks or race conditions.
This analogy can be seen as reflective of the broader societal challenges of resource allocation, labor, and the means of production. The dining philosophers problem and the management of file descriptors in a 
shell both highlight the importance of structured, fair systems for resource allocation to prevent deadlock (stagnation) and ensure productive harmony. This can be interpreted as a microcosm of societal labor 
dynamics, where the means of production (resources) must be managed efficiently and fairly to prevent conflict and ensure the wellbeing of all participants.

## Characteristics

Minishell is a miniature shell program based on Bash. Minishell supports:

* Prompt display
* Command history (`up` and `down` arrows)
* System executables available from the environment (`ls`, `cat`, `grep`, etc.)
* Local executables (`./minishell`)
* Builtin commands :
    * `echo` (and option `-n`)
    * `cd` (with only a relative or absolute path)
    * `pwd` (no options)
    * `export` (no options)
    * `unset` (no options)
    * `env` (no options or arguments)
    * `exit` (with exit number but no other options)
    * Pipes `|` which redirect output from one command to input for the next
* Redirections:
    * `>` redirects output
    * `>>` redirects output in append mode
    * `<` redirects input
    * `<< DELIMITER` displays a new prompt, reads user input until reaching DELIMITER, redirects user input to command input (does not update history)
* Environment variables (i.e. `$USER` or `$VAR`) that expand to their values.
* `$?` expands to the exit status of the most recently executed foreground pipeline.
* User keyboard signals:
    * `ctrl-c` displays a new prompt line.
    * `ctrl-d` exits minishell
    * `ctrl-\` does nothing

MiniShell's code is modular, with implementation order `lexer -> parser -> expander -> executor`. The modular components are:

* **Parsing**: Handling user input and breaking it down into commands and arguments.
* **Execution**: Running the parsed commands using system calls like `fork()`, `exec()`, and `waitpid()`.
* **Built-ins**: Implementing shell built-in commands like `cd`, `echo`, `setenv`, `unsetenv`, `env`, and `exit`.
* **Redirection and Piping**: Managing input/output redirection (`>`, `<`, `>>`) and piping between commands (`|`).
* **Signal Handling**: Dealing with signals like `SIGINT` and `SIGCHLD`.
* **Environment**: Storing and modifying the shell's environment variables.

Please, note that this MiniShell has nothing to do with mini shotgun shells.

## General description (how MiniShell works)

The shell is a program that interacts with the user through a terminal or takes the input from a file and executes a sequence of commands that are passed to the Operating System. A shell program, like MiniShell, 
is an application that allows interacting with the computer. In a shell the user can run programs and also redirect the input to come from a file and output to come from a file. Shells also provide programming 
constructions such as if, for, while, functions, variables etc. Additionally, shell programs offer features such as line editing, history, file completion, wildcards, environment variable expansion, and 
programming constructions. MiniShell is all in all a fairly faithful reproduction of Bash: the GNU shell, the most common shell program. Like Gaul, the MiniShell implementation is divided into three parts: the 
**parser**, the **executor** and the **shell subsystems**.
The parser is the software component that reads the **command line** and puts it into a data structure that will store the commands that will be executed. The executor takes the structure generated by the parser 
and creates a new process for every **atomic formula** in the command line. The executor also creates changes to the outputs for every **functor**, like logical operators, pipes and redirections, in the command 
line. MiniShell has **environment variables** as a shell subsystem: an environment variable is a user-definable value that can affect the way running processes will behave on a computer. It uses **wildcards** 
that expand arguments of the form `string*string` to all the files that match them. It also allows the use of **subshells**.

Each parser is composed of a **lexer** and a **parser**: the lexer takes the input characters and puts the characters together into words called **tokens**; the parser processes the tokens according to a 
**grammar in the Backus­-Naur form**. **Commands** are handled through a dedicated type and stored into an array by the parser.
The lexer separates input into tokens by reading characters from the standard input and trying to match them with a set of **regular expressions**. The parser takes the tokens generated by the lexical analyzer 
and checks if they follow the syntax described by the grammar rules through **semantic actions**.
The executor starts by creating a new process for each command in the **pipeline** and making the parent wait for the last command. The parent process does all the piping and redirection before forking the 
processes, so that the children inherits the redirection. The parent saves input/output and restores it in the end.

Firstly, the execution of a shell script involves the invocation of the interpreter, which then proceeds to parse the given commands. These commands may either reside within the shell itself or exist as external 
programs. The latter necessitate the spawning of new processes, thus expanding the scope of the original process tree. File descriptors serve as abstract representations of open files or other communication 
channels, enabling the reading and writing of data. In the case of a shell, these descriptors facilitate the exchange of information between the user and the system.

## Synchronization

Both shells and the dining philosophers problem deal with synchronization, but they tackle different aspects of it.
Shells interact with file descriptors for tasks like reading from and writing to files, pipes, and network sockets. While each file descriptor represents a resource, access to that resource may need to be 
controlled to avoid conflicts. However, this isn't directly related to the specific problem of synchronization between multiple processes.
The dining philosophers problem focuses on synchronizing access to shared resources between multiple processes. In the classic scenario, five philosophers share five forks, and each needs two forks to eat. The 
challenge is to design a protocol that ensures no philosopher starves while preventing two neighbors from grabbing both forks simultaneously, leading to deadlock.
Shells manage individual file descriptors for different processes. Potential conflicts in shells include concurrent read/write access to the same file or improper closing of descriptors leading to resource leaks: 
solutions involve proper use of locking mechanisms, non-blocking I/O, and resource cleanup.
The dining philosophers problem deals with synchronizing access to a fixed number of shared resources (forks) between multiple processes and focuses on preventing deadlock and ensuring fair access: solutions 
involve using semaphores, monitors, or other synchronization primitives.
The relationship between shells working on file descriptors and synchronization problems like the dining philosophers problem lies in the need for managing shared resources (file descriptors in the case of 
shells, and chopsticks in the dining philosophers problem) in a concurrent environment. Both scenarios require careful synchronization to avoid deadlocks and ensure that each process or thread can access the 
resources it needs without interfering with others. In shell programming and operating systems, file descriptors are a limited resource used to represent open files, sockets, pipes, and other I/O streams. When 
multiple processes or threads attempt to read from or write to the same file descriptor without proper synchronization, it can lead to race conditions, where the output or the behavior depends on the sequence of 
execution of the processes or threads. This is similar to the dining philosophers problem in that both involve managing access to shared resources in a way that avoids deadlock and ensures fairness. The dining 
philosophers problem is a classic synchronization problem that involves philosophers sitting around a table with a chopstick between each pair. A philosopher needs both chopsticks to eat. The challenge is to 
design a protocol that allows all philosophers to eat without ever getting into a deadlock situation, where each philosopher is holding one chopstick and waiting for the other, thus preventing anyone from eating.
The main challenge in both scenarios is preventing deadlocks while allowing concurrent access to shared resources. In the case of file descriptors, mechanisms like locking (using `flock` or similar tools) can be 
employed to ensure that only one process can write to a file at a time, similar to how semaphores or mutexes are used in the dining philosophers problem to manage access to chopsticks. Careful design is needed to 
prevent starvation, where a process or thread is perpetually denied access to the resources it needs.
Shells that work with file descriptors are related to synchronization problems like the dining philosophers problem because both scenarios involve resource management and concurrent access to shared resources. In 
the case of shells working with file descriptors, file descriptors represent a way to interact with files, pipes, sockets, or other resources. When a shell spawns multiple processes or handles input/output 
redirection, it needs to manage these file descriptors to ensure proper communication and data flow between processes. This can introduce synchronization concerns, such as avoiding race conditions, handling data 
consistency, and managing access to shared resources. Similarly, the dining philosophers problem is a classic synchronization problem that illustrates the challenges of resource allocation and concurrent access. 
In this problem, a group of philosophers sits at a table, with each philosopher needing two forks to eat. The challenge is to design a protocol that prevents deadlock and ensures fair access to forks by all 
philosophers.

## Summary

A shell is a specialized program that interprets and executes commands entered by the user. It serves as a command interpreter, facilitating the interaction between the user and the underlying operating system. 
When it comes to shells, one cannot overlook the significance of the Bourne Again Shell (bash). Bash, a GNU project's reimplementation of the Bourne shell, is widely regarded as one of the most popular shells on 
Linux. Shells are not limited to interactive use; they also serve as interpreters for shell scripts. These scripts are text files containing shell commands, akin to programs written in programming languages. 
Consequently, shells provide facilities such as variables, loop and conditional statements, enabling the interpretation and execution of shell scripts. The Bourne shell includes built-in commands, while bash 
offers a more extensive range of built-in commands. 
Shells, are command interpreters that facilitate the execution of programs in an operating system. They serve as an interface between the user and the underlying system, allowing users to interact with the system 
by executing commands and managing processes. File descriptors, on the other hand, are a mechanism used in Unix-like operating systems to access files and other input/output (I/O) resources. Shells often employ 
file descriptors to handle input and output redirection, piping, and other forms of interprocess communication. These file descriptors serve as communication channels between processes, enabling data to flow from 
one process to another. In the case of piping, for instance, a shell creates a pipe, which is a unidirectional communication channel, to connect the output of one process to the input of another process. This 
allows for the seamless transfer of data between processes.
The dining philosophers problem involves a group of philosophers sitting around a table, each contemplating the meaning of life and hungering for sustenance. In front of each philosopher lies a plate of 
spaghetti, and between each pair of philosophers, there is a single fork. The challenge arises when the philosophers attempt to eat. They must acquire both the fork to their left and the fork to their right to 
indulge in their culinary desires. However, there are only as many forks as there are philosophers, leading to a potential deadlock situation. If each philosopher simultaneously picks up the fork to their left, 
they will be left waiting indefinitely for the fork to their right, resulting in a deadlock. The dining philosophers problem is an illustration of the challenges that arise when multiple processes contend for 
shared resources. In the case of the philosophers, the shared resource is the fork. Similarly, in the realm of shells and file descriptors, processes contend for access to shared I/O resources, such as pipes. 
Guessing the scenario where multiple processes, orchestrated by a shell, attempt to read from or write to a pipe simultaneously: without proper synchronization mechanisms, these processes may encounter 
synchronization issues akin to the dining philosophers problem. For instance, if multiple processes attempt to read from a pipe simultaneously, they may end up in a state of deadlock, waiting indefinitely for 
data that may never arrive. In the case of the dining philosophers problem, various strategies, such as the use of locks or semaphores, can be employed to ensure that philosophers acquire the necessary forks in a 
coordinated manner. Similarly, in the realm of shells and file descriptors, synchronization mechanisms, such as locks or signals, can be utilized to coordinate access to shared I/O resources and prevent issues 
such as deadlock or data races.
