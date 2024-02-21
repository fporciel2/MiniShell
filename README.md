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
The lexer separates input into tokens by reading characters from the standard input and trying to match them with a set of **regular expressions**. 
