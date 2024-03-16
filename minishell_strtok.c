/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_strtok.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:33:59 by fporciel          #+#    #+#             */
/*   Updated: 2024/03/16 14:48:48 by fporciel         ###   ########.fr       */
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
 *
 * MiniShell uses a two-step process to tokenize the input.
 *
 * 1. Quote removal:
 *
 * 	* The shell scans the input string from left to right.
 * 	* It identifies any opening and closing quotes (single, `'`, or double,
 * 	`"`).
 * 	* It proceeds with quote removal (see below `QUOTE REMOVAL` for details).
 *
 * 2. Tokenization:
 *
 * 	* The shell splits the remaining string into words (tokens) based on a set
 * 	of delimiters defined by the IFS (Internal Field Separator) variable.
 * 	* By default, IFS includes characters like space, tab (\t), newline (\n),
 * 	and sometimes carriage return (\r), depending on the system.
 * 	* Any consecutive delimiters are treated as a single separator.
 * 	* Text enclosed within quotes is treated as a single token, regardless of
 * 	delimiters inside the quotes.
 *
 * 	PSEUDOCODE
 *
 * 	function msh_strtok(input_string) {
 * 		#Step 1: Quote Removal (loop through characters)
 * 		for char in input_string:
 * 			if char is a quote:
 * 				#Track opening/closing quotes and remove the outermost pairs
 * 				#(implementation details below)
 * 			else:
 * 				#Append character to the processed string
 * 				processed_string += char
 * 		#Step 2: Tokenization
 * 		tokens = []
 * 		current_token = ""
 * 		for char in processed_string:
 * 			if char is in IFS:
 * 				#Delimiter encountered, add current token (unless empty)
 * 				if current_token:
 * 					tokens.append(current_token)
 * 				current_token = ""
 * 			else:
 * 				#Append character to the current token
 * 				current_token += char
 * 		#Add the last token (if not empty)
 * 		if current_token:
 * 			tokens.append(current_token)
 * 		return tokens
 * 	}
 */

#include "minishell.h"

void	msh_strtok(t_input *init)
{
}
