#include "minishell.h"

int	ft_pwd(t_cmd *cmd, t_mshell *mini)
{
	char	buf[PATH_MAX];

	(void)cmd;
	(void)mini;
	if (!getcwd(buf, PATH_MAX))
		return (1);
	printf("%s\n", buf);
	return (0);
}
