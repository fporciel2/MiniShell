#include "minishell.h"

static void	free_paths(char **paths)
{
	char	**tmp;

	tmp = paths;
	while (*tmp)
	{
		free(*tmp);
		tmp++;
	}
	free(paths);
}

static char	*find_cmd_path(t_cmd *cmd, t_env *env_head)
{
	char	*path;
	char	**paths;
	char	*tmp;
	int		i;

	if (ft_strchr(cmd->name, '/'))
		return (ft_strdup(cmd->name));
	path = env_get(env_head, "PATH");
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		tmp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp, cmd->name);
		free(tmp);
		if (!access(path, F_OK))
			return (free_paths(paths), path);
		free(path);
	}
	return (free_paths(paths), perror("minishell: command not found"), NULL);
}

int	execute_external(t_cmd *cmd, t_mshell *mini)
{
	char	**argv;
	char	**envp;
	char	*path;

	argv = cmd->argv;
	envp = mini->envp;
	path = find_cmd_path(cmd, mini->env);
	if (!path)
		return (127);
	free(argv[0]);
	argv[0] = path;
	if (execve(path, argv, envp) == -1)
	{
		perror("execve");
		return (126);
	}
	return (0);
}
