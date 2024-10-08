/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_info_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtasi <mwojtasi@student.42lyon.fr >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 16:48:51 by mwojtasi          #+#    #+#             */
/*   Updated: 2024/08/10 21:49:16 by mwojtasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_word_num(t_lexer *lex)
{
	size_t	num;

	num = 0;
	while (lex && lex->type != T_PIPE)
	{
		if (lex->value && (lex->type == T_WORD || lex->type == T_S_QUOTED_WORD
				|| lex->type == T_D_QUOTED_WORD))
			num++;
		if (lex->value && (lex->type == T_REDIR_IN || lex->type == T_REDIR_OUT
				|| lex->type == T_APPEND_OUT))
			num--;
		lex = lex->next;
	}
	return (num);
}

t_token_type	get_lexer_type(char *line)
{
	if (line[0] == '"' )
		return (T_D_QUOTED_WORD);
	else if (line[0] == '\'')
		return (T_S_QUOTED_WORD);
	else if (line[0] == '|')
		return (T_PIPE);
	else if (line[0] == '<')
	{
		if (line[1] == '<')
			return (T_HERE_DOC);
		else
			return (T_REDIR_IN);
	}
	else if (line[0] == '>')
	{
		if (line[1] == '>')
			return (T_APPEND_OUT);
		else
			return (T_REDIR_OUT);
	}
	else
		return (T_WORD);
}

char	*get_token_type(t_token_type type)
{
	if (type == T_WORD)
		return ("T_WORD");
	else if (type == T_PIPE)
		return ("T_PIPE");
	else if (type == T_REDIR_IN)
		return ("T_REDIR_IN");
	else if (type == T_REDIR_OUT)
		return ("T_REDIR_OUT");
	else if (type == T_APPEND_OUT)
		return ("T_APPEND_OUT");
	else if (type == T_D_QUOTED_WORD)
		return ("T_D_QUOTED_WORD");
	else if (type == T_S_QUOTED_WORD)
		return ("T_S_QUOTED_WORD");
	else if (type == T_HERE_DOC)
		return ("T_HERE_DOC");
	else
		return ("UNKNOWN");
}

t_lexer	*get_last_lexer(t_lexer *lex)
{
	while (lex && lex->next)
		lex = lex->next;
	return (lex);
}

t_lexer	*get_first_lexer(t_lexer *lex)
{
	while (lex && lex->prev)
		lex = lex->prev;
	return (lex);
}
