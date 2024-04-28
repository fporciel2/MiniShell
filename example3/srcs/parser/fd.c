#include "minishell.h"

void	close_fd(t_cmd *cmd)
{
	if (cmd->fdin != STDIN_FILENO)
	{
		close(cmd->fdin);
		cmd->fdin = STDIN_FILENO;
	}
	if (cmd->fdout != STDOUT_FILENO)
	{
		close(cmd->fdout);
		cmd->fdout = STDOUT_FILENO;
	}
}
