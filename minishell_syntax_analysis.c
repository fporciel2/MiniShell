/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_syntax_analysis.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:45:49 by fporciel          #+#    #+#             */
/*   Updated: 2024/04/17 18:05:42 by fporciel         ###   ########.fr       */
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

int	msh_is_quoted(char *str)
{
	ssize_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 39)
			return (1);
		else if (str[i] == 34)
			return (2);
		i++;
	}
	return (0);
}

static void	msh_perform_expansion(t_cmd *head, t_input *init)
{
	ssize_t	i;

	i = 0;
	while (head->argv[init->i][i])
	{
		if (head->argv[init->i][i] == 36)
		{
			head->argv = msh_normal_exp(head, init);
			if (init->err_xpand)
				return ;
			i = 0;
			continue ;
		}
		i++;
	}
}

static void	msh_cautiously_expand(t_cmd *head, t_input *init)
{
	ssize_t	i;

	i = 0;
	while (head->argv[init->i][i])
	{
		if (head->argv[init->i][i] == 36)
		{
			if (!msh_is_in_quotes(head->argv[init->i], i))
				head->argv = msh_normal_exp(head, init);
			else if (!msh_is_in_single_quotes(head->argv[init->i], i))
				head->argv = msh_double_quotes_exp(head, init);
			else
			{
				i++;
				continue ;
			}
			if (init->err_xpand)
				return ;
			i = 0;
			continue ;
		}
	}
}

int	msh_parsing(t_cmd *head, t_input *init)
{
	init->err_xpand = 1;
	while (head)
	{
		init->i = 0;
		while (head->argv[init->i])
		{
			if (!msh_is_quoted(head->argv[init->i]))
				msh_perform_expansion(head, init);
			else
				msh_cautiously_expand(head, init);
		}
		head = head->next;
	}
	return (init->err_xpand);
}
