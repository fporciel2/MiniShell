/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_first_get_env.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:36:53 by fporciel          #+#    #+#             */
/*   Updated: 2024/03/22 10:09:35 by fporciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* `MiniShell` is a simple shell for Debian GNU/Linux.
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

static int	msh_clean_envs(char **envs, size_t i)
{
	i--;
	while (envs[i])
	{
		free(envs[i]);
		i--;
	}
	free(envs);
	return (0);
}

char	*msh_strdup(char *env)
{
	size_t	i;
	char	*str;

	i = 0;
	if (!env)
		return (NULL);
	while (env[i])
		i++;
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (env[i])
	{
		str[i] = env[i];
		i++;
	}
	str[i] = 0;
	return (str);
}

int	msh_first_get_env(char **envp, char ***envs)
{
	size_t	i;

	i = 0;
	if (!envp)
		return (0);
	while (envp[i])
		i++;
	*envs = (char **)malloc(sizeof(char *) * (i + 1));
	if (!*envs)
		return (0);
	(*envs)[i] = NULL;
	i = 0;
	while (envp[i])
	{
		(*envs)[i] = msh_strdup(envp[i]);
		if (!(*envs)[i])
			return (msh_clean_envs(*envs, i));
		i++;
	}
	return (1);
}
