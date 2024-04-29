/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 07:27:23 by fporciel          #+#    #+#             */
/*   Updated: 2024/04/29 07:42:11 by fporciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>
# include <errno.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <dirent.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <sys/param.h>
# include <sys/resource.h>
# include <sys/time.h>
// Useful Definitions
# define PROMPT "minishell$ "
# define HERE_DOC_PROMPT "heredoc> "
# define MAX_FD 4096
# define ERROR_INVALID_COMMAND "Error: Invalid command."
# define ERROR_FILE_NOT_FOUND "Error: File not found."
# define ERROR_PERMISSION_DENIED "Error: Permission denied."
# define ERROR_COMMAND_NOT_FOUND "Error: Command not found."
# define ERROR_ARGUMENT_REQUIRED "Error: Argument required."
# define ERROR_TOO_MANY_ARGUMENTS "Error: Too many arguments."
# define ERROR_INTERNAL "Error: An internal error occurred."

#endif