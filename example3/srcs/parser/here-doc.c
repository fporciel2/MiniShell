#include "minishell.h"

// int	init_here_doc(t_cmd *cmd, char *hdoc)
// {
// 	int		fd[2];
// 	char	*line;

// 	if (!hdoc)
// 	{
// 		printf("Error");
// 		return (1);
// 	}
// 	if (pipe(fd) == -1)
// 		return (1);
// 	while (42)
// 	{
// 		printf("> ");
// 		line = get_next_line(STDIN);
// 		printf("\nline: \"%s\"\n", line);
// 		if (!line || str_equals(line, hdoc))
// 			break ;
// 		write(fd[1], line, ft_strlen(line));
// 		write(fd[1], "\n", 1);
// 		free(line);
// 	}
// 	if (line)
// 		free(line);
// 	close(fd[1]);
// 	cmd->fdin = fd[0];
// 	return (0);
// }
