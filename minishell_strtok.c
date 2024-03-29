/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_strtok.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:33:59 by fporciel          #+#    #+#             */
/*   Updated: 2024/03/28 08:27:23 by fporciel         ###   ########.fr       */
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
 * 1. Quote tracking:
 *
 * 	* The shell scans the input string from left to right.
 * 	* It identifies any opening and closing quotes (single, `'`, or double,
 * 	`"`).
 * 	* It tracks the indexes of opening and closing quotes.
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
 * 		#Step 1: Quote Tracking (loop through characters)
 * 		for char in input_string:
 * 			if char is a quote:
 * 				#Track opening/closing quotes
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
 *
 * EXPLANATION
 *
 * 	* The `msh_strtok` function takes the input string as input.
* 	* The first loop iterates through each character and handles quote tracking.
* 	* The processed string is then tokenized based on delimiters in the IFS
* 	variable.
* 	* Another loop iterates through the processed string:
* 		* If a delimiter is encountered, the current token (if not empty) is
* 		added to the list of tokens, and the current token is reset.
* 		* Otherwise, the character is appended to the current token.
* 	* Finally, the last token (if not empty) is added to the list before
* 	returning the list of tokens.
*
* THE QUOTE TRACKING IMPLEMENTATION
*
* MiniShell needs to keep track of whether it's currently inside a quoted string
* to correctly parse the command line. This involves identifying the start of a
* quoted string (an opening quote) and its end (a closing quote). MiniShell
* supports two types of quotes: single quotes - `'` - and double quotes - `"`- .
*
* To track quotes, MiniShell uses a simple state machine:
*
* PSEUDOCODE
*
* 	Initialize state to NORMAL
* 	Initialize error to FALSE
* 	for each character in input:
* 		if state is NORMAL:
* 			if character is a single quote:
* 				change state to SINGLE_QUOTE
* 			else if character is a double quote:
* 				change state to DOUBLE_QUOTE
* 			else:
* 				process character normally
* 		else if state is SINGLE_QUOTE:
* 			if character is a single quote:
* 				change state to NORMAL
* 			else:
* 				process character as part of a single-quoted string
* 		else if state is DOUBLE_QUOTE:
* 			if character is a double quote:
* 				change state to NORMAL
* 			else:
* 				process character as part of a double-quoted string
*
* 	if state is SINGLE_QUOTE or DOUBLE_QUOTE:
* 		set error state to TRUE
*
* EXPLANATION
*
* The above pseudocode outline a basic state machine with three states:
*
* 1. NORMAL: The defauls state where characters are processed normally. If a
* quote is encountered, the state changes to either SINGLE_QUOTE or DOUBLE_QUOTE
* depending on the type of quote.
* 2. SINGLE_QUOTE: In this state, all characters are treated as part of a
* single-quoted string until another single quote is encountered, which switches
* the state back to NORMAL. Single-quoted strings preserve the literal value of
* each character within the quotes.
* 3. DOUBLE_QUOTES: Similar to SINGLE_QUOTE, but for double-quoted strings. The
* state remains DOUBLE_QUOTE until another double quote is encountered.
* Double-quoted strings also preserve the literal value of characters but allow
* certain expansions (like variable expansion).
*
* An unclosed quote typically results in a continuation prompt, allowing the
* user to continue the command on the next line and complete the quotation.
* However, if the input ends without a closing quote, MiniShell considers this a
* syntax error.
*/

#include "minishell.h"

/*The `msh_quote_state` state machine handles the quote tracking and sets
 * eventually the `open_quote` variable to 1 if the closing quote is missing,
 * so that the command line can wait appropriately for the input continuation
 * and the closing quote, based on the `open_quote` and `quote_state` variables.
 * */
static int	msh_quote_state(t_input *init, char quote)
{
	if (quote == 34)
		init->quote_state = DOUBLE_QUOTE;
	else
		init->quote_state = SINGLE_QUOTE;
	msh_append_char(init);
	init->i++;
	while (init->string[init->i] && (init->string[init->i] != quote))
	{
		msh_append_char(init);
		init->i++;
	}
	if (init->string[init->i])
	{
		msh_append_char(init);
		init->quote_state = NORMAL;
	}
	else
		init->open_quote = 1;
	return (init->open_quote);
}

/*`msh_is_ifs` detects whether the current character is a delimiter. It doesn't
 * check whether the eventual `newline` character follows the escape character.
 * That will be checked by the quotation remover.*/
static int	msh_is_ifs(t_input *init)
{
	if ((((init->string[init->i] == 32) || (init->string[init->i] == 9)
		|| (init->string[init->i] == 13) || (init->string[init->i] == 10))
		&& ((init->i == 0) || (init->string[init->i - 1] != 92)))
		|| ((init->string[init->i] == 60) && ((init->i == 0)
			|| (init->string[init->i - 1] != 60)
			|| ((init->string[init->i - 1] == 60) && ((init->i - 1) != 0)
				&& (init->string[init->i - 2] == 60))))
		|| ((init->string[init->i] == 62) && ((init->i == 0)
			|| (init->string[init->i - 1] != 62)
			|| ((init->string[init->i - 1] == 62) && ((init->i - 1) != 0)
				&& (init->string[init->i - 2] == 62)))))
		return (1);
	return (0);
}

/* `msh_is_pipe` detects whether the current character is an actual pipe or a
 * literal pipe or another character.*/
static int	msh_is_pipe(t_input *init)
{
	if ((init->string[init->i] == 124)
		&& ((init->i == 0) || (init->string[init->i - 1] != 92)))
		return (1);
	return (0);
}

/* `msh_strtok` slides the input string looking for delimiters, quotes, pipes or
 * simple characters to append, calling a different function for any case.*/
int	msh_strtok(t_input *init)
{
	init->error = 1;
	while (init->error && init->string[init->i])
	{
		if (((init->string[init->i] == 34) || (init->string[init->i] == 39))
			&& ((init->i == 0) || (init->string[init->i - 1] != 92)))
			init->error = msh_quote_state(init, init->string[init->i]);
		else if (msh_is_ifs(init))
		{
			while (msh_is_ifs(init))
				init->i++;
			init->error = msh_split_token(init);
		}
		else if (msh_is_pipe(init))
			init->error = msh_split_pipeline(init);
		else
			init->error = msh_append_char(init);
		init->i++;
	}
	return (init->error);
}
