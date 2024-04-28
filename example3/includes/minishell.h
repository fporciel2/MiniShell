/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorenzogaudino <lorenzogaudino@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 12:12:50 by lorenzogaud       #+#    #+#             */
/*   Updated: 2024/04/24 15:23:49 by lorenzogaud      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define _DEFAULT_SOURCE
# define _POSIX_C_SOURCE
# define START 0
# define COUNT_COMMANDS 1
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
# include <limits.h>
# include <dirent.h>
# include "./../libft/libft.h"

static const volatile sig_atomic_t	g_last_signal;

typedef struct s_cmd	t_cmd;
typedef struct s_mshell	t_mshell;

typedef int							(*t_bdn_func)(t_cmd *, t_mshell *);

typedef struct s_input
{
	char	**envp;
	char	*string;
	char	***pipeline;
}			t_input;

typedef struct s_cmd
{
	char			*name;
	char			**argv;
	int				argc;
	int				fdin;
	int				fdout;
	struct s_cmd	*next;
	struct s_cmd	*prev;
	t_bdn_func		buildin;
}					t_cmd;

typedef enum e_redirection
{
	IN			= 1,
	OUT			= 2,
	OUT_APPEND	= 3,
	HERE_DOC	= 4,
}	t_redirection;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_mshell
{
	t_env	*env;
	t_cmd	*cmd;
	char	**envp;
	int		exit_code;
	int		to_exit;
}			t_mshell;

/* Initialization functions. */
void		msh_init(char **envp, t_input *init);
void		msh_handle_sigint(int sig);
void		msh_handle_igquit(int sig);
/* Main loop's functions. */
void		msh_loop(t_input *init);
/* Tokenizer/Lexicon-analyzer's functions.*/
void		msh_strtok(t_input *init);
void		msh_clean_pipeline(t_input *init);
/* Cleaning functions. */
void		msh_cleanup(t_input *init);
void		msh_close_on_error(t_input *init);

/* Parser */

void		free_cmds(t_cmd *cmd_head);
void		print_cmds(t_cmd *cmd);
t_cmd		*parser(t_input *init);
t_cmd		*init_cmd(t_cmd *prev, int argv_count);
void		close_fd(t_cmd *cmd);

/* Env */

t_env		*env_init(char **envp);
t_env		*env_init_elm(char *name, char *value);
t_env		*env_from_str(char *str);
int			env_set(t_env **env_head, char *name, char *value, int append);
void		env_unset(t_env **env_head, char *name);
void		print_env(t_env *env_head); // solo per test
void		free_env(t_env **env_head);
int			env_find_split_index(char *env_str);
t_env		*env_get_elm(t_env *env_head, char *name);
char		*env_get(t_env *env_head, char *name);
int			parse_here_doc(t_cmd *cmd, char *arg);
void		env_append(t_env **env_head, t_env *new_env);
t_env		*env_sort(t_env *env_head);
t_env		*env_cpy(t_env *env_head);
void		free_env_array(char **env);
char		**env_to_array(t_env *env_head);

/* Utils*/

int			str_equals(char *str1, char *str2);
int			ft_isstrdigit(char *str);

/* Build in */

int			ft_cd(t_cmd *cmd, t_mshell *mini);
int			ft_echo(t_cmd *cmd, t_mshell *mini);
int			ft_env(t_cmd *cmd, t_mshell *mini);
int			ft_exit(t_cmd *cmd, t_mshell *mini);
int			ft_pwd(t_cmd *cmd, t_mshell *mini);
int			ft_unset(t_cmd *cmd, t_mshell *mini);
int			ft_export(t_cmd *cmd, t_mshell *mini);

t_bdn_func	ft_is_buildin(t_cmd *cmd);

/* executer */

int			msh_execution(t_mshell *mshell);
int			redirect(t_cmd *cmd);
int			execute_cmd(t_cmd *cmd, t_mshell *mini);
int			execute_external(t_cmd *cmd, t_mshell *mini);
int			check_exit(t_mshell *mshell);

/* pipes */
int			execute_with_pipes(t_cmd *cmd, t_mshell *mini);

/* testing */
// void 	printOpenFileDescriptors(pid_t pid);

#endif