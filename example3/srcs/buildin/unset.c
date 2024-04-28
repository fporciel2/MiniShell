#include "minishell.h"

int	ft_unset(t_cmd *cmd, t_mshell *mini)
{
	char	**argv;

	argv = cmd->argv;
	while (++argv && *argv)
		env_unset(&mini->env, *argv);
	return (0);
}
