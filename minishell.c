/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:14:31 by fporciel          #+#    #+#             */
/*   Updated: 2024/03/25 15:47:42 by fporciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ´MiniShell´ is a simple shell for Debian GNU/Linux.
 * Copyright (C) 2024 Federico Porciello
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 * 
 * For more information on how to contact me by electronic and paper mail
 * please see:
 * https://github.com/fporciel2/MiniShell
 */

#include "minishell.h"

static int	msh_remove_envs(char **envs)
{
	ssize_t	i;

	i = 0;
	while (envs[i])
		i++;
	i--;
	while (i >= 0)
	{
		free(envs[i]);
		i--;
	}
	return (free(envs), perror("Error"), errno);
}

int	main(int argc, char **argv, char **envp)
{
	t_input	*init;
	char	**envs;

	if ((argc != 1) || !envp || !msh_first_get_env(envp, &envs))
		return (perror("Error"), errno);
	init = (t_input *)malloc(sizeof(t_input));
	if (!init)
		return (msh_remove_envs(envs));
	msh_init(envs, init);
	msh_loop(init);
	msh_loop_clean_all(init);
	init = NULL;
	(void)argv;
	return (42);
}
