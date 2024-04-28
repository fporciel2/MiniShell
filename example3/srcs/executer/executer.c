#include "minishell.h"

// Funzione per ottenere i file descriptor aperti per un processo
// void printOpenFileDescriptors(pid_t pid) {
// 	// Costruzione del percorso alla directory dei file descriptor del processo
// 	char proc_fd_path[256];
// 	snprintf(proc_fd_path, sizeof(proc_fd_path), "/proc/%d/fd", pid);

// 	// Apertura della directory
// 	DIR *dir = opendir(proc_fd_path);
// 	if (dir == NULL) {
// 		perror("Errore nell'apertura della directory");
// 		return;
// 	}

// 	// Lettura dei file descriptor aperti
// 	struct dirent *entry;
// 	fprintf(stderr, "File descriptor aperti per il processo %d:\n", pid);
// 	while ((entry = readdir(dir)) != NULL) {
// 		// Ignora le voci speciali "." e ".."
// 		if (strcmp(entry->d_name, ".") == 0 
//			|| strcmp(entry->d_name, "..") == 0) {
// 			continue;
// 		}

// 		// Stampa il numero del file descriptor
// 		fprintf(stderr, "%s\n", entry->d_name);
// 	}

// 	// Chiusura della directory
// 	closedir(dir);
// }

// static int	execute_external(t_cmd *cmd, t_mshell *mini)
// {
// 	// TESTING:
// 	// read from fdin and write in fdout
// 	char buf[500];
// 	int n;

// 	while ((n = read(0, buf, sizeof(buf))) > 0)
// 	{
// 		fprintf(stderr, "n: %d\n", n);
// 		if (write(1, buf, n) < 0)
// 			break ;
// 	}
// 	return (0);
// }

int	execute_cmd(t_cmd *cmd, t_mshell *mini)
{
	t_bdn_func	b_fun;
	int			ret;

	if (redirect(cmd))
		return (1);
	b_fun = ft_is_buildin(cmd);
	if (b_fun != NULL)
		ret = b_fun(cmd, mini);
	else
		ret = execute_external(cmd, mini);
	return (ret);
}

int	msh_execution(t_mshell *mshell)
{
	t_cmd	*cmd;
	int		result;

	cmd = mshell->cmd;
	if (check_exit(mshell))
		return (0);
	while (cmd)
	{
		if (!ft_is_buildin(cmd))
		{
			if (mshell->envp)
				free_env_array(mshell->envp);
			mshell->envp = env_to_array(mshell->env);
			if (!(mshell->envp))
				return (1);
		}
		if (execute_with_pipes(cmd, mshell))
			return (1);
		cmd = cmd->next;
	}
	while (waitpid(-1, &result, 0) > 0)
		if (WIFEXITED(result))
			mshell->exit_code = WEXITSTATUS(result);
	return (0);
}
