/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_expansions_substitutions.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 07:23:41 by fporciel          #+#    #+#             */
/*   Updated: 2024/04/18 08:32:44 by fporciel         ###   ########.fr       */
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

static char	**msh_expand_env1(t_cmd *head, t_input *init, char *str, ssize_t i)
{
	while (head->envp[head->env_num][head->start_path])
	{
		head->subst = msh_new_char(head->subst,
				head->envp[head->env_num][head->start_path++]);
		if (head->subst == NULL)
			return (msh_interrupt_expansion(init, str), NULL);
	}
	while (str[post_path])
	{
		head->subst = msh_new_char(head->subst, str[post_path++]);
		if (head->subst == NULL)
			return (msh_interrupt_expansion(init, str), NULL);
	}
}

char	**msh_expand_env(t_cmd *head, t_input *init, char *str, ssize_t i)
{
	head->env_num = msh_is_env(str, i, head->envp);
	head->start_path = msh_get_path_index(head->envp[head->env_num]);
	head->post_path = msh_get_post_path(str, i);
	head->pre_i = 0;
	head->subst = NULL;
	while (head->pre_i != i)
	{
		head->subst = msh_new_char(head->subst, str[head->pre_i++]);
		if (head->subst == NULL)
			return (msh_interrupt_expansion(init, str), NULL);
	}
	return (msh_expand_env1(t_cmd *head, t_input *init, char *str, ssize_t i));
}
