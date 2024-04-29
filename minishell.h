/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:12:09 by fporciel          #+#    #+#             */
/*   Updated: 2024/04/29 16:54:02 by fporciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
 * `MiniShell` is a simple shell for Debian GNU/Linux.
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
 */

#ifndef MINISHELL_H
# define MINISHELL_H
# define _DEFAULT_SOURCE
# define _POSIX_C_SOURCE
# define BAD_START "Minishell doesn't take arguments yet."
# define SYS_CALL_ERROR "Program crashed: "
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

typedef struct s_msh
{
	char	**envp;
}			t_msh;

/* PRINT ERRORS */
int		msh_error(char *str1, char *str2, char *str3);
/* CALCULATE LENGTH */
ssize_t	msh_strlen(char *str);
ssize_t	msh_matlen(char **mat);
/* DUPLICATE ITEMS */
char	*msh_strdup(char *str);
char	**msh_matdup(char **mat);
/* CLEAN UP */
char	*msh_clean_str(char *str);
int		msh_clean_matrix(char ***mat, int i);

#endif
