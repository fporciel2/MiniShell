/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:19:53 by fporciel          #+#    #+#             */
/*   Updated: 2024/03/28 08:23:16 by fporciel         ###   ########.fr       */
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
 * The MiniShell program is a simplified version of a Unix shell, like bash,
 * which is a command-line interpreter that provides a user interface for the
 * Unix operating system. The purpose of the MiniShell program is to serve as an
 * educational project for students at School 42, where they can learn about and
 * implement core functionalities of a shell. This includes understanding how a
 * shell interprets and executes commands, manages processes, handles file
 * descriptors, and interacts with the environment.
 *
 * The general structure of the MiniShell program involves several key
 * components that work together to process and execute user commands:
 *
 * 1 - COMMAND LINE INTERFACE (CLI). This is where the user inputs commands. The
 * MiniShell program needs to provide a prompt and handle input, including
 * maintaining a history of executed commands.
 *
 * 2 - COMMAND PARSING. The input from the CLI must be parsed to separate the
 * command and its arguments, handle quoting, and identify any special
 * characters or operators.
 *
 * 3 - BUILT-IN COMMANDS. MiniShell should implement several built-in commands
 * like 'echo', 'cd', 'pwd', 'export', 'unset', 'env', and 'exit'.
 *
 * 4 - EXECUTION. After parsing, the shell must search for the appropriate
 * executable based on the command, which could involve looking in the 'PATH'
 * environment variable or using a specified path.
 *
 * 5 - REDIRECTION AND PIPES. The shell should be able to redirect input and
 * output using '<', '>', ´<<´ and ´>>´, as well as handle pipes (´|´) to pass
 * the output of one command as input to another.
 *
 * 6 - ENVIRONMENT VARIABLES. MiniShell must manage environment variables,
 * allowing for expansion and modification.
 *
 * 7 - SIGNAL HANDLING. The program should handle errors gracefully, including
 * command not found, permission denied, and other common error conditions.
 *
 * 9 - MEMORY MANAGEMENT. All dynamically allocated memory must be properly
 * managed to avoid memory leaks.
 *
 * The relations between these different parts are:
 *
 * * The CLI feeds user input to the COMMAND PARSING component.
 * * COMMAND PARSING interprets the input and prepares it for EXECUTION.
 * * BUILT-IN COMMANDS are executed internally without searching for external
 * executables.
 * * EXECUTION may involve creating new processes, which requires correct SIGNAL
 * HANDLING and ENVIRONMENT VARIABLE management.
 * * REDIRECTION AND PIPES after how the shell handles standard input, output,
 * and error streams during command execution.
 * * Throughout the process, MEMORY MANAGEMENT ensures that resources are
 * allocated and freed appropriately.
 *
 * The design of the MiniShell program should follow the guidelines and
 * restrictions of the Norm coding standard, which includes rules on naming
 * conventions, file structure, allowed functions, and more. The project's
 * Makefile must compile the source files with the flags ´-Wall´, ´-Wextra´ and
 * ´-Werror´.
 * For the bonus part of the project, students can implement logical operators
 * (´&&´ and ´||´) and wildcard expansion (´*´), but this is only evaluated if
 * the mandatory part is perfectly completed.
 */

#ifndef MINISHELL_H
# define MINISHELL_H
# define _DEFAULT_SOURCE
# define _POSIX_C_SOURCE
# define START 0
# define NO_ERROR 0
# define NORMAL 0
# define SINGLE_QUOTE 1
# define DOUBLE_QUOTE 2
# define OPEN_PIPE 1
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

typedef struct s_input
{
	char	**envp;
	char	*string;
	char	***pipeline;
	size_t	pipe_count;
	size_t	token_count;
	size_t	i;
	int		open_quote;
	int		quote_state;
	int		pipe_state;
	int		error;
}			t_input;

/* Initialization functions. */
int		msh_first_get_env(char **envp, char ***envs);
void	msh_init(char **envp, t_input *init);
void	msh_handle_sigint(int sig);
void	msh_handle_igquit(int sig);
void	msh_initialize(t_input *init);
/* Main loop's functions. */
void	msh_loop(t_input *init);
/* Tokenizer/Lexicon-analyzer's functions.*/
int		msh_strtok(t_input *init);
int		msh_split_token(t_input *init);
int		msh_split_pipeline(t_input *init);
int		msh_append_char(t_input *init);
/* Cleaning functions. */
void	msh_loop_clean_all(t_input *init);
void	msh_loop_memset(t_input *init);
void	msh_split_clean_pipeline(t_input *init);
void	msh_split_clean_command(char **command);
/* Closing functions. */
void	msh_init_close_on_error(t_input *init);
void	msh_handle_sigint_close_on_error(const t_input *init);
/* Utils functions. */
char	*msh_strdup(char *env);

#endif
