#include "minishell.h"

// TODO: spostare
static void	sig_quit(int sig)
{
	(void)sig;
	perror("Quit");
	exit(0);
}

static int	use_pipe(t_cmd *cmd)
{
	return ((cmd != NULL) && (cmd->next != NULL));
}

static void	set_pipe_out(t_cmd *cmd, int *fd)
{
	if (!use_pipe(cmd))
		return ;
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
}

static void	set_pipe_in(t_cmd *cmd, int *fd)
{
	if (!use_pipe(cmd))
		return ;
	close(fd[1]);
	if (cmd->next->fdin == STDIN_FILENO)
		cmd->next->fdin = fd[0];
	else
		close(fd[0]);
}

int	execute_with_pipes(t_cmd *cmd, t_mshell *mini)
{
	int	fd[2];
	int	pid;
	int	ret;

	if (!cmd)
		return (0);
	if (use_pipe(cmd) && pipe(fd) == -1)
		return (1);
	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		set_pipe_out(cmd, fd);
		signal(SIGQUIT, sig_quit);
		ret = execute_cmd(cmd, mini);
		free_cmds(mini->cmd);
		free_env(&mini->env); // TODO: cambiare con il free di tutta la struttura
		free_env_array(mini->envp);
		exit(ret);
	}
	set_pipe_in(cmd, fd);
	close_fd(cmd);
	return (0);
}
