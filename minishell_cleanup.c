/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_cleanup.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 11:31:59 by fporciel          #+#    #+#             */
/*   Updated: 2024/03/19 12:11:38 by fporciel         ###   ########.fr       */
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

void	msh_clean_envp(char **envp)
{
	size_t	i;

	i = 0;
	if (!envp)
		return ;
	while (envp[i])
		i++;
	while (envp[--i])
	{
		free(envp[i]);
		envp[i] = NULL;
	}
	free(envp);
}

void	msh_clean_pipeline(t_input *init)
{
}

void	msh_close_on_error(t_input *init)
{
	if (init)
	{
		if (init->envp)
			msh_clean_envp(init->envp);
		if (init->string)
			free(init->string);
		if (init->pipeline)
			msh_clean_pipeline(init);
		msh_cleanup(init);
	}
	perror(strerror(errno));
	exit(EXIT_FAILURE);
}

void	msh_cleanup(t_input *init)
{
	free(init);
}
