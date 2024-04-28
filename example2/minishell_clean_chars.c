/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_clean_chars.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 06:52:42 by fporciel          #+#    #+#             */
/*   Updated: 2024/03/30 07:00:55 by fporciel         ###   ########.fr       */
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

char	***msh_clean_pipeline(char ***pipeline)
{
	ssize_t	i;

	if (!pipeline)
		return (NULL);
	i = msh_pipelen(pipeline);
	i--;
	while (i >= 0)
	{
		pipeline[i] = msh_clean_cmd(pipeline[i]);
		i--;
	}
	free(pipeline);
	return (NULL);
}

char	**msh_clean_cmd(char **cmd)
{
	ssize_t	i;

	if (!cmd)
		return (NULL);
	i = msh_cmdlen(cmd);
	i--;
	while (i >= 0)
	{
		cmd[i] = msh_clean_str(cmd[i]);
		i--;
	}
	free(cmd);
	return (NULL);
}

char	*msh_clean_str(char *str)
{
	if (str)
		free(str);
	return (NULL);
}
