/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 06:32:15 by fporciel          #+#    #+#             */
/*   Updated: 2024/04/24 05:05:00 by fporciel         ###   ########.fr       */
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

typedef struct s_cmd
{
	char			*name;
	char			**argv;
	char			**envp;
	int				argc;
	int				fdin;
	int				fdout;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}					t_cmd;

typedef struct s_tok
{
	char			*str;
	int				type;
	int				index;
	struct s_tok	*next;
	struct s_tok	*prev;
}					t_tok;

typedef struct s_input
{
	struct s_cmd	*cmds;
	struct s_tok	*toks;
	char			**envp;
	char			*line;
	char			*prompt;
	ssize_t			i;
	int				errquote;
	int				heredoc;
	int				pipe;
	int				errtok;
	int				space;
	int				exit_flag;
	unsigned char	exit_status;
}					t_input;

/* MATRIX */
int		msh_get_matrix(char **source, char ***dest);
ssize_t	msh_matlen(char **matrix);
int		msh_matdel(char ***matrix);
/* STRING */
char	*msh_strdup(char *str);
ssize_t	msh_strlen(char *str);
char	*msh_strcpy(char *dest, char *src);
/* SIGNAL */
int		msh_set_signals(void);
void	msh_handle_sigint(int sig);
/* LOOP */
int		msh_loop(t_input *init);
/* INIT */
void	msh_init(t_input *init);
void	msh_memset(t_input *init);
void	msh_clean_init(t_input **init);
/* STRTOK */
int		msh_strtok(t_input *init);

#endif
