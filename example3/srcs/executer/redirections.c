#include "minishell.h"

int	redirect(t_cmd *cmd)
{
	if (cmd->fdout != STDOUT_FILENO)
	{
		if (dup2(cmd->fdout, STDOUT_FILENO) == -1)
			return (1);
		close(cmd->fdout);
		cmd->fdout = STDOUT_FILENO;
	}
	if (cmd->fdin != STDIN_FILENO)
	{
		if (dup2(cmd->fdin, STDIN_FILENO) == -1)
			return (1);
		close(cmd->fdin);
		cmd->fdin = STDIN_FILENO;
	}
	return (0);
}
