/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorenzogaudino <lorenzogaudino@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 12:11:01 by lorenzogaud       #+#    #+#             */
/*   Updated: 2024/04/24 15:34:29 by lorenzogaud      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_input init;
	char *arg1[] = {"exit", "1", NULL};
	// char *arg2[] = {"cat", NULL};
	char *arg3[] = {"cat", NULL};
	char *arg4[] = {"ls", NULL};
	// char *arg4[] = {"a", "-", NULL};
	// char *arg5[] = {"aa", NULL};

	(void)argv;
	(void)argc;

	// get cmd from argv
	// char **arg1 = ft_split(argv[1], ' ');

	// char **pipeline[] = {arg1, NULL};

	char **pipeline[] = {arg1, NULL, arg3, arg4, NULL};

	init.string = NULL;
	init.pipeline = pipeline;

	// parse
	t_cmd *result = parser(&init);

	// Stampa del risultato utilizzando la funzione print_cmds
	// print_cmds(result);

	// print dell'envp
	t_env	*env_head;

	env_head = env_init(envp);
	// env_export(&env_head, "MARIUS=1");
	// env_export(&env_head, "MARIUS");
	// env_export(&env_head, "MARIUS=");
	// env_export(&env_head, "MARIUS");

	t_mshell msh;

	msh.env = env_head;
	msh.cmd = result;
	msh.envp = NULL;
	msh.exit_code = 0;
	msh.to_exit = 0;

	msh_execution(&msh);
	printf("TO EXIT: %d\nEXIT CODE: %d\n", msh.to_exit, msh.exit_code);
	free_env(&env_head);
	free_cmds(result);
	free_env_array(msh.envp);
	return (0);
}
