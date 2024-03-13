/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:19:53 by fporciel          #+#    #+#             */
/*   Updated: 2024/03/13 14:04:38 by fporciel         ###   ########.fr       */
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
 * GENERAL STRUCTURE OF THE PROGRAM
 *
 * 1 - Some concepts.
 *
 * * Processes.
 * 	A process in computing is an instance of a computer program that is being
 * 	executed. It contains the program code and its current activity. Each
 * 	process has a unique process identifier (PID), and the operating system
 * 	manages multiple processes through process scheduling.
 *
 * 	* Creation and Terminantion.
 * 		Processes are created through system calls such as 'fork()' in Unix-like
 * 		operating systems. The 'fork()' system call creates a new process by
 * 		duplicating the current process. The new process is called the child
 * 		process, and the original process is the parent. Processes are
 * 		terminated by calling 'exit()', and a parent process can wait for a
 * 		child process to terminate using 'wait()' or 'waitpid()'.
 * 	* Execution.
 * 		To execute a new program with a process, the 'execve()' system call is
 * 		used. It replaces the current process's memory space with a new program.
 *
 * * File Descriptors.
 * 	File descriptors are abstract indicators used to access files or other
 * 	input/output resources, such as pipes and sockets. The standard file
 * 	descriptors are 0 (standard input, 'stdin'), 1 (standard output, 'stdout'),
 * 	and 2 (standard error, 'stderr').
 *
 * 	 * Manipulation.
 * 	 	Functions like 'open(), 'read()', 'write()', and 'close()' are used to
 * 	 	manipulate file descriptors. Redirection in a shell is achieved by
 * 	 	duplicating file descriptors using 'dup()' or 'sup2()'.
 *
 * * Memory Management.
 * 	Memory management involves allocating and deallocating memory as needed by a
 * 	program. Dynamic memory allocation in C is handled through 'malloc()',
 * 	'calloc()', 'realloc()', and 'free()'.
 *
 * * Command Parsing.
 * 	Parsing involves breaking down the command input by the user into a format
 * 	that can be easily executed by the shell.
 * 	 
 * 	 * Techniques.
 * 	 	A tokenizer splits the input into tokens, which are then organized into
 * 	 	a syntax tree or a similar structure. Quotations and escapes are handled
 * 	 	in this phase.
 *
 * *Signal Handling.
 * 	Signals are a form of inter-process communication. They are used to notify a
 * 	process of events like interrupts.
 * 	 
 * 	 *Implementation.
 * 	 	'signal()' or 'sigaction()' are used to set up signal handlers within
 * 	 	MiniShell. Common signals include SIGINT (Ctrl+c), SIGQUIT (Ctrl-$$) and
 * 	 	SIGTSTP (Ctrl+Z).
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
