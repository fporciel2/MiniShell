#include "minishell.h"

/* allocate memory for a new command 
   init the cmd with prev next and default values */
t_cmd	*init_cmd(t_cmd *prev, int argv_count)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->next = NULL;
	cmd->prev = prev;
	cmd->name = NULL;
	cmd->buildin = NULL;
	cmd->argc = argv_count;
	if (argv_count > 0)
	{
		cmd->argv = (char **)malloc(sizeof(char *) * (argv_count + 1));
		if (!cmd->argv)
			return (NULL);
		cmd->argv[argv_count] = NULL;
	}
	else
		cmd->argv = NULL;
	cmd->fdin = STDIN_FILENO;
	cmd->fdout = STDOUT_FILENO;
	return (cmd);
}

void	free_cmds(t_cmd *cmd_head)
{
	t_cmd	*tmp;
	int		i;

	while (cmd_head)
	{
		tmp = cmd_head;
		i = -1;
		while (cmd_head->argv && cmd_head->argv[++i])
			free(cmd_head->argv[i]);
		free(cmd_head->argv);
		free(cmd_head->name);
		close_fd(cmd_head);
		cmd_head = cmd_head->next;
		free(tmp);
	}
}

// void	print_cmds(t_cmd *cmd)
// {
// 	char	*arg;

// 	while (cmd != NULL)
// 	{
// 		printf("\n---\ncmd->name: %s\n", cmd->name);
// 		printf("fdin: %d, fdout: %d\n", cmd->fdin, cmd->fdout);
// 		for (int i = 0; cmd->argv && cmd->argv[i]; i++)
// 		{
// 			arg = cmd->argv[i];
// 			printf("cmd->argv[%d]: %s\n", i, arg);
// 		}
// 		cmd = cmd->next;
// 	}
// }
