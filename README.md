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


 MINISHELL PROJECT OVERVIEW

 The Minishell project is an educational assignment typically given to students at programming schools such as School 42. The goal of the project is to create a simplified version of a Unix shell, which is a command-line interpreter that provides a user interface for the Unix operating system. The project is designed to teach students about processes, file descriptors, and the inner workings of shells like bash or zsh.

 PROJECT REQUIREMENTS

 The Minishell project has several key requirements that students must fulfill:

 * PROMPT DISPLAY: The shell must display a prompt when waiting for new commands.
 * COMMAND HISTORY: The shell should maintain a history of commands that have been entered.
 * EXECUTABLE SEARCH: The shell must be able to search for and launch executables based on the PATH environment variable or using relative or absolute paths.
 * GLOBAL VARIABLE LIMITATION: The use of global variables should be minimized, with a strong recommendation to use only one, which must be justified.
 * SPECIAL CHARACTERS: The shell should not interpret unclosed quotes or non-essential special characters like backslashes or semicolons unless required by the project.
 * QUOTES HANDLING: Single quotes should prevent interpretation of meta-characters, while double quotes should allow for the expansion of environment variables denoted by the dollar sign.
 * REDIRECTIONS AND PIPES: The shell must implement input and output redirections (`<`, `>`, `>>`, `<<`) and pipes (`|`).
 * ENVIRONMENT VARIABLES: The shell should handle the expansion of environment variables.
 * EXIT STATUS: The shell should handle the exit status of commands using the `$?` variable.
 * SIGNAL HANDLING: The shell must handle signals such as `ctrl-C`, `ctrl-D`, and `ctrl-\`.
 * BUILT-IN COMMANDS: The shell should implement a few built-in commands like `echo`, `cd`, `pwd`, `export`, `unset`, `env`, and `exit`.

 LEARNING OUTCOMES

 By completing the Minishell project, students are expected to gain a solid understanding of:

 * BASH SYNTAX: Through the implementation of a shell, students learn the syntax and behavior of bash commands.
 * SHELL IMPLEMENTATION: Students explore how a shell is implemented, typically divided into parsing, execution, and handling of shell subsystems.
 * PROCESSES AND FILE DESCRIPTORS: The project provides insights into how Unix processes work, how file descriptors are used, and how inter-process communication is handled.
 * SIGNAL HANDLING: Students learn how to manage signals sent to processes, which is crucial for creating a responsive command-line interface.
 * MEMORY MANAGEMENT: Proper allocation and deallocation of memory are essential to prevent leaks, which is a critical aspect of the project.

 RESOURCES AND TESTING

 Students are often provided with resources such as documentation, libraries (like `libft` for School 42 students), and testing frameworks to help them develop and test their shells. They are encouraged to write modular and understandable code and to document their work for future reference and collaboration.

 PROJECT VALIDATION

 The Minishell project is typically reviewed and graded by peers or automated systems, and students are expected to defend their work by explaining their design choices and demonstrating the functionality of their shell.

 EXAMPLES AND COMMUNITY

 There are numerous examples of Minishell projects available on platforms like GitHub, where students share their code and collaborate. These repositories often include detailed explanations of the project's features, how to compile and run the shell, and any additional functionalities implemented by the students.

 GENERAL DESCRIPTION

 A Minishell project involves creating a simple shell program, which is a user interface for access to an operating system's services. In essence, it is a basic version of a command-line interpreter, similar to bash (Bourne Again SHell), which is one of the most common shells in Unix-like operating systems. The purpose of such a project is educational; it is designed to teach students about system programming concepts such as processes and file descriptors.

 Processes are instances of running programs. When you create a shell, you need to be able to launch and manage these processes. This often involves using system calls like `fork()` to create new processes and `exec()` to replace the process's memory space with a new program.

 File descriptors are an abstraction for representing and managing open files within an operating system. In the context of a shell, file descriptors are crucial for handling input and output redirection, piping between processes, and managing files.

 The Minishell project, as described, is an educational endeavor aimed at creating a simplified version of a shell, similar to bash. This project is particularly valuable for understanding the inner workings of shells in Unix-like operating systems. Here are the key learning aspects and components involved in the Minishell project:

 PROCESSES

 In the context of Minishell, you will delve into how shells manage processes. This includes how to start and terminate processes, and how the shell interacts with these processes. Understanding process creation (using system calls like `fork()` and `exec()`) and process management is crucial. This knowledge is foundational for implementing features such as executing commands or handling background processes.

 FILE DESCRIPTORS

 File descriptors are integral to how Unix-like systems handle files and input/output operations. In the Minishell project, you will learn about managing file descriptors for standard input, output, and error streams. manipulating these file descriptors is essential for redirecting input and output, which are common features in full-fledged shells.

 CREATING A SIMPLE SHELL

 The core objective of the Minishell project is to build a shell that can interpret and execute commands from the user. This involves parsing user input, executing commands, and providing appropriate outputs. The project helps in understanding command line interpretation, environment variable management, and the integration of various Unix utilities.

 SHELL (COMPUTING)

A user interface for access to an operating system's services.

DEFINITION: A shell is a computer program that provides an interface for users or other programs to access an operating system's services.
INTERFACE TYPES: Shells use either a command-line interface (CLI) or graphical user interface (GUI).
PURPOSE: Named for its position as the outermost layer around the operating system.

Early computing required direct interaction with hardware using binary inputs, which was cumbersome and not intuitive for most users. The development of command-line interfaces (CLIs) and shells was a significant advancement in making computers more accessible and easier to use.

HISTORICAL CONTEXT OF SHELLS

The concept of a shell in computing emerged as a solution to the limitations of early computer interaction methods, which often involved using switches or punch cards to enter commands directly in binary form. This method was indeed "seriously irritating" and inefficient for users. The shell, acting as a command-line interpreter, allowed users to input commands in a more human-readable form, which the system would then interpret and execute.

The development of the shell is closely tied to the history of operating systems, particularly Unix. The first Unix shell, the Thompson shell, was developed by Ken Thompson in the early 1970s as a simple command interpreter. Other shells, such as the Bourne shell and the C shell, followed and added features like scripting capabilities and improved user interfaces.

EVOLUTION AND SIGNIFCANCE OF SHELLS

Shells have evolved significantly since their inception. They now offer features like scripting, command history, and command completion, which enhance user productivity and system manageability. Shells also serve as a critical interface for system administrators and programmers to interact with the operating system more efficiently.

The Minishell project, as part of educational programs like those at school 42, reflects the ongoing relevance of shells. By building a Minishell, students not only learn about the history and functionality of shells but also gain a deeper understanding of operating system concepts like process management, file handling, and inter-process communication.

EDUCATIONAL VALUE OF MINISHELL

The Minishell project allows students to experience firsthand the challenges and solutions that early developers faced before the advent of more sophisticated graphical user interfaces (GUIs). This project serves as a bridge connecting them with the foundational concepts of computing and operating system design.

In summary, the development of shells was a logical and necessary advancement to make computing more accessible and to abstract the complexity of hardware interactions into a more user-friendly command-line interface. Projects like Minishell not only pay homage to these historical developments but also provide valuable educational experiences, underscoring the enduring importance of shells in the field of computer science.

The statement that "the existence of shells is linked to the very existence of IT" is accurate in the sense that shells have been a fundamental component of computer operating systems since their early development. Shells provide a user interface that allows for easier interaction with the operating system through command-line inputs, which is more intuitive than using binary switches or punch cards, methods were common in the earliest computers.

The development of shell environments was indeed driven by the need for more user-friendly methods of communicating with computers. Early computing required detailed and cumbersome methods of interaction, often involving direct manipulation of hardware or use of binary code. The introduction of command-line interfaces (CLIs), like shells, allowed users to input commands in a format that was closer to natural language, albeit still highly structured and syntactic.

The Minishell project, as described in your summary, serves as an educational tool that simulates these early environments. It allows students to experience firsthand the types of challenges and limitations that were common before the advent of more sophisticated graphical user interfaces (GUIs) and modern operating systems like Windows. By building a simple shell, students can gain a deeper understanding of how commands are processed and executed by the operating system, and how user input can be managed through processes and file descriptors.

This project not only teaches technical skills related to programming and system design but also provides historical insight into the evolution of user interfaces in computing. It highlights the progression from primitive, non-interactive systems to the complex, user-friendly interfaces we use today. Thus, Minishell acts as a sort of "time machine", allowing students to revisit and engage with the foundational concepts and challangese of early computing.