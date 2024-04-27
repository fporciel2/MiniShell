/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 11:20:33 by fporciel          #+#    #+#             */
/*   Updated: 2024/04/27 11:40:59 by fporciel         ###   ########.fr       */
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
