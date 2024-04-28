// #include "minishell.h"

// int	is_redirection(char *str)
// {
// 	if (str_equals(str, ">") || str_equals(str, ">>") || str_equals(str, "<"))
// 		return (1);
// 	return (0);
// }

// int	syntax(char ***pipeline)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (pipeline[i])
// 	{
// 		j = 0;
// 		while (pipeline[i][j])
// 		{
// 			if (is_redirection(pipeline[i][j]))
// 			{
// 				if (!pipeline[i][j + 1])
// 					return (0);
// 				if (is_redirection(pipeline[i][j + 1]))
// 					return (0);
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (1);
// }
