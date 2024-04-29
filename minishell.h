/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 11:20:33 by fporciel          #+#    #+#             */
/*   Updated: 2024/04/28 09:51:49 by fporciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
 * 'MiniShell' is a simple shell for Debian GNU/Linux.
 * Copyright (C) 2024 Federico Porciello
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 *
 * For more information on how to contact me by electronic and paper mail
 * please see:
 * https://github.com/fporciel2/MiniShell
 *
 * MINISHELL PROJECT OVERVIEW
 *
 * The Minishell project is an educational assignment from School 42, a coding
 * school with a unique pedagogical approach that emphasizes peer-to-peer
 * learning and project-based education. The project's primary goal is for
 * students to create a simplified version of a Unix shell, which is a
 * command-line interpreter that provides a user interface for the Unix
 * operating system.
 *
 * KEY ASPECTS OF THE MINISHELL PROJECT
 *
 * 	* Complexity and Learning Curve: The project is described as complex and
 * 	time-consuming, offering a deep dive into the intricacies of shell
 * 	programming and the Unix environment.
 * 	* Core Features: Students are expected to implement basic shell
 * 	functionalities such as displaying a prompt, handling commands, and 
 * 	manging file descriptors and processes.
 * 	* Code Quality and Collaboration: The project encourages writing clean,
 * 	modular code and maintaining good documentation. It also emphasizes the
 * 	importance of collaboration, as students often work in pairs.
 * 	* Technical Skills: Through the Minishell project, students gain a solid
 * 	understanding of bash syntax, how shells work, and the implementation of
 * 	shells, which typically involves lexical analysis, parsing, expansion, and
 * 	execution.
 * 	* Testing and Tools: Students are provided with tools like
 * 	`minishell-test` for testing their shell implementations against predefined
 * 	tests. They also learn about file descriptors and their managemen, which is
 * 	crucial for handling input/output operations within the shell.
 * 	* Real-world Coding Experience: The project simulates real-world coding
 * 	challenges, requiring students to deal with a codebase that may exceed their
 * 	short-term memory capacity and to write code that is understandable to
 * 	others.
 * 	* Project Submission: The project culminates in a submission to a git
 * 	repository, which is then peer-reviewed and graded.
 *
 * 	EDUCATIONAL VALUE
 *
 * 	The Minishell project serves as a practical exercise that consolidates
 * 	knowledge in several areas:
 *
 * 	* Unix Systems: Students learn about the Unix operating system and how to
 * 	interact with it through a shell.
 * 	* Programming Skills: The project enhances students' programming skills in
 * 	C, focusing on system-level programming.
 * 	* Problem-Solving: Students are challenged to solve complex problems that
 * 	require a deep understanding of the system's workings.
 * 	* Collaboration: Working in pairs, students learn to collaborate
 * 	effectively, which is a critical skill in software development.
 * 	* Documentation: The necessity of maintaining clear documentation is
 * 	emphasized, which is a key aspect of any large software project.
 * 
 * CONCLUSION
 *
 * The Minishell project is a comprehensive educational ssignment that not only
 * teaches students about shell programming and Unix systems but also hones
 * their software development skills in a collaborative environment. It is a
 * testament to the hands-on, project-based learning approach of School 42,
 * preparing students for the challenges of real-world software development.
 *
 * SHELL (COMPUTING)
 * 
 * A user interface for access to an operating system's services.
 *
 * DEFINITION: A shell is a computer program that provides an interface for
 * users or other programs to access an operating system's services.
 *
 * INTERFACE TYPES: Shells use either a command-line interface (CLI) or
 * graphical user interface (GUI).
 *
 * PURPOSE: Named for its position as the outermost layer around the operating
 * system.
 *
 * USE CASE: The choice between CLI or GUI often depends on the computer's role
 * and specific operations.
 *
 * Early computing required direct interaction with hardware, often through
 * binary switches or punch cards, which was a cumbersome and error-prone
 * process. The development of command-line interfaces was a significant
 * advancement because it allowed users to interact with computers using typed
 * commands, which were more intuitive and closer to natural language.
 *
 * The Minishell project is an educational tool that simulates the experience of
 * using a shell in the early days of computing, before the advent of modern
 * graphical user interfaces (GUIs) and operating systems like Windows. By
 * creating a simple shell, users can gain an appreciation for the challenges
 * faced by early computer users and developers, and understand the evolution of
 * human-computer interaction from basic command-line inputs to the
 * sophisticated interfaces we use today.
 *
 * The project serves as a bridge to the past, providing insight into the
 * foundational technologies of information technology and the importance of
 * shells in the history of computing. It also underscores the enduring
 * relevance of command-line interfaces, which remain a powerful tool for system
 * administration, software development, and automation, despite the prevalence
 * of graphical user interfaces in contemporary computing.
 *
 * The Minishell project must be written in the C programming language. This
 * requirement is explicitly stated in the project guidelines, ensuring that
 * students adhere to specific technical standards and use the appropriate
 * programming language for system-level programming tasks like shell
 * implementation.
 *
 * The Minishell project, like all projects at School 42, must adhere to the
 * school's coding standards known as the "Norm". This set of rules is designed
 * to ensure consistency, readability, and maintainability of code among
 * students. The Norm includes specific guidelines such as limiting the number
 * of lines in a function, restricting the use of certain language features, and
 * enforcing naming conventions.
 *
 * For the Minishell project, adherence to the Norm is crucial not only for the
 * main project files but also for any bonus files or functions you might
 * include. If there is a norm error in any part of your project, including the
 * bonus sections, you will receive a score of zero for the norm check. This
 * emphasizes the importance of thorough checking and compliance with the Norm
 * throughout the development process. Tools like Norminette are provided to
 * help students check their code against these standards before submission.
 *
 * It is crucial that your functions do not terminate unexpectedly due to errors
 * such as segmentation faults, bus errors, or double frees. Suche unexpected
 * terminations are indicative of critical bugs in the program, which can render
 * the project non-functional.
 *
 * If your project exhibits any of these critical errors during evaluation, it
 * will be considered non-functional and will receive a score of zero. This
 * underscores the necessity of thorough testing and debugging to ensure that
 * your shell is stable and behaves predictably under various conditions.
 * Ensuring the proper management of memory and handling of system calls are key
 * areas to focus on to prevent these types of errors.
 *
 * In the Minishell project, it is crucial to ensure that all heap-allocated
 * memory is properly managed and freed when no longer needed. Memory leaks,
 * where allocated memory is not correctly freed, can lead to increased memory
 * usage and reduced performance, and are not tolerated in this project.
 *
 * BEST PRACTICES FOR MEMORY MANAGEMENT IN MINISHELL
 *
 * 1. PROPER ALLOCATION AND DEALLOCATION: Use `malloc`, `calloc`, or similar
 * functions to allocate memory and ensure that every allocation is paired with
 * a corresponding `free` to avoid memory leaks. This is crucial in functions
 * where multiple return points could bypass the freeing of allocated memory.
 * 2. USE OF VALGRIND OR SIMILAR TOOLS: Tools like `Valgrind` cna be used to
 * detect memory leaks and other memory-related errors. These tools are
 * invaluable for ensuring that all allocated memory is properly freed before
 * the program exits.
 * 3. STRUCTURED ERROR HANDLING: Implement error handling that frees any
 * allocated memory when an error occurs before exiting a function. This is
 * particularly important in a project like Minishell, where different parts of
 * the shell may fail or exit unexpectedly.
 * 4. AVOID MEMORY LEAKS IN CHILD PROCESSES: When using `fork()` and `execve()`
 * for command execution, ensure that any memory allocated in the parent process
 * is properly managed. Memory leaks can occurr if the child process exits
 * unexpectedly or if `execve()` fails and the allocated memory is not freed.
 * 5. REGULAR CODE REVIEWS: Regularly review your code or have it reviewed by
 * peers to catch potential memory leaks. This practice can help identify areas
 * where memory may not be properly managed.
 * 6. TESTING: Implement comprehensive tests to check for memory leaks under
 * various scenarios. This can include automated tests that check the memory
 * status before and after shell operations.
 * 7. DOCUMENTATION AND COMMENTS: Document any complex memory management logic
 * clearly in the code. Comments can help maintainers understand why certain
 * memory management decisions were made and how to handle changes without
 * introducing leaks.
 *
 * CONCLUSION
 *
 * Memory management is a critical aspect of the Minishell project. By adhering
 * to best practices for allocating and freeing memory, using tools to detect
 * leaks, and incorporating thorough testing and documentation, you can ensure
 * that the Minishell remains efficient and leak-free. This approach not only
 * meets the project requirements but also enhances the overall stability and
 * performance of the shell.
 *
 */

#ifndef MINISHELL_H
# define MINISHELL_H
# define _DEFAULT_SOURCE
# define _POSIX_C_SOURCE
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <signal.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include <term.h>

#endif
