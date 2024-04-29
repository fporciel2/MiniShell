/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:15:05 by fporciel          #+#    #+#             */
/*   Updated: 2024/04/29 17:06:14 by fporciel         ###   ########.fr       */
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

int	main(int argc, char **argv, char **envp)
{
	t_msh	msh;

	if (argc != 1)
		return (msh_error(BAD_START, NULL, NULL));
	(void)argv;
	if (envp)
	{
		printf("ENVP: \n\n");
		ssize_t i = 0;
		while (envp[i])
		{
			printf("%s\n", envp[i]);
			i++;
		}
		printf("\n\n");
	}
	msh.envp = msh_matdup(envp);
	if (!msh.envp)
		return (msh_error(SYS_CALL_ERROR, strerror(errno), NULL));
	printf("ENVP_COPY: \n\n");
	ssize_t i = 0;
	while (msh.envp[i])
	{
		printf("%s\n", msh.envp[i]);
		i++;
	}
	printf("\n\n");
	msh.envp = msh_clean_matrix(msh.envp);
	return (msh_error("NO ERRORS", NULL, NULL));
}
