#include "minishell.h"

/* parse the redirections */
static int	save_fd(t_cmd *cmd, t_redirection red_type, char *filename)
{
	if (!filename)
		return (1);
	if (red_type == IN && cmd->fdin != STDIN_FILENO)
		close(cmd->fdin);
	else if ((red_type == OUT || red_type == OUT_APPEND)
		&& cmd->fdout != STDOUT_FILENO)
		close(cmd->fdout);
	if (red_type == IN)
		cmd->fdin = open(filename, O_RDONLY);
	else if (red_type == OUT)
		cmd->fdout = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	else if (red_type == OUT_APPEND)
		cmd->fdout = open(filename, O_WRONLY | O_CREAT | O_APPEND, S_IRWXU);
	if (cmd->fdin == -1 || cmd->fdout == -1)
	{
		perror("minishell: ");
		perror(strerror(errno));
		return (close_fd(cmd), 1);
	}
	return (0);
}

/* Save fd of here doc */
int	parse_here_doc(t_cmd *cmd, char *arg)
{
	if (!arg)
		return (1);
	if (cmd->fdin != STDIN_FILENO)
		close(cmd->fdin);
	cmd->fdin = ft_atoi(arg);
	return (0);
}

/* parse the arguments of the command */
int	parse_redirection(t_cmd *cmd, char **argv)
{
	if (strncmp(*argv, "<", 2) == 0)
		return (save_fd(cmd, IN, *(++argv)));
	else if (strncmp(*argv, ">", 2) == 0)
		return (save_fd(cmd, OUT, *(++argv)));
	else if (strncmp(*argv, ">>", 3) == 0)
		return (save_fd(cmd, OUT_APPEND, *(++argv)));
	else if (strncmp(*argv, "<<", 3) == 0)
		return (parse_here_doc(cmd, *(++argv)));
	return (1);
}

int	is_redirection(char *str)
{
	if (str_equals(str, ">") || str_equals(str, ">>")
		|| str_equals(str, "<") || str_equals(str, "<<"))
		return (1);
	return (0);
}

int	count_argv(char **argv)
{
	int	i;
	int	result;
	int	r_count;

	i = 0;
	r_count = 0;
	while (argv[i])
	{
		if (is_redirection(argv[i]))
			r_count++;
		i++;
	}
	result = i - r_count * 2;
	if (result < 0)
		return (0);
	return (result);
}

int	parse_cmd(char **argv, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (*argv)
	{
		if (is_redirection(*argv))
		{
			if (parse_redirection(cmd, argv))
				return (1);
			argv++;
		}
		else
		{
			cmd->argv[i] = ft_strdup(*argv);
			if (!cmd->argv[i++])
				return (1);
			if (i == 1)
				cmd->name = ft_strdup(cmd->argv[0]);
		}
		argv++;
	}
	return (0);
}

/* parse the input and create the command list */
t_cmd	*parser(t_input *init)
{
	int		i;
	t_cmd	*cmd;
	t_cmd	*cmd_head;
	int		argv_count;

	i = -1;
	cmd_head = NULL;
	while (init->pipeline[++i])
	{
		argv_count = count_argv(init->pipeline[i]);
		if (!cmd_head)
		{
			cmd = init_cmd(NULL, argv_count);
			cmd_head = cmd;
		}
		else
		{
			cmd->next = init_cmd(cmd, argv_count);
			cmd = cmd->next;
		}
		if (!cmd || parse_cmd(init->pipeline[i], cmd))
			return (NULL);
	}
	return (cmd_head);
}
