/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtasi <mwojtasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:35:17 by mwojtasi          #+#    #+#             */
/*   Updated: 2024/05/14 01:39:49 by mwojtasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// test
static inline int	is_operator_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

void add_lexer_type(t_lexer **new, char *line)
{
	if (line[0] == '"' )
		(*new)->type = T_D_QUOTED_WORD;
	else if (line[0] == '\'')
		(*new)->type = T_S_QUOTED_WORD;
	else if ((*new)->value[0] == '|')
		(*new)->type = T_PIPE;
	else if ((*new)->value[0] == '<')
	{
		if ((*new)->value[1] == '<')
			(*new)->type = T_HERE_DOC;
		else
			(*new)->type = T_REDIR_IN;
	}
	else if ((*new)->value[0] == '>')
	{
		if ((*new)->value[1] == '>')
			(*new)->type = T_APPEND_OUT;
		else
			(*new)->type = T_REDIR_OUT;
	}
	else
		(*new)->type = T_WORD;
	(*new)->next = NULL;
}

void append_new_lexer(t_lexer **lex, t_lexer **new)
{
	t_lexer *tmp;

	if (*lex == NULL)
	{
		*lex = *new;
		(*lex)->prev = NULL;
	}
	else
	{
		tmp = *lex;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = *new;
		(*new)->prev = tmp;
	}
}


int is_n_only_spaces(char *line, size_t size)
{
	size_t i;

	i = 0;
	while (i < size)
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n' 
			&& line[i] != '\v' && line[i] != '\f' && line[i] != '\r')
			return (0);
		i++;
	}
	return (1);
}

int	new_lexer(t_lexer **lex, char *line, size_t size)
{
	t_lexer	*new;
	char	*trim;
	
	if (!line || !line[0])
		return (0);
	if (is_n_only_spaces(line, size))
		return (0);
	new = malloc(sizeof(t_lexer));
	if (new == NULL)
		return (1); //TODO: free exit
	new->value = malloc(size + 1);
	if (new->value == NULL)
		return (1); //TODO: free exit
	//printf("%.*s\n", (int)size, line);
	if (line[0] == '"' || line[0] == '\'')
		ft_strlcpy(new->value, line + 1, size);
	else
	{
		ft_strlcpy(new->value, line, size + 1); //TODO: check return
		trim = new->value;
		new->value = ft_strtrim(new->value, " "); // TODO: check return
		free(trim);
	}
	add_lexer_type(&new, line);
	append_new_lexer(lex, &new);
	// temp code
	printf("value: %s\n", new->value);
	printf("type: %d\n\n", new->type);
	return (0);
}


void	free_lexer(t_lexer *lex)
{
	t_lexer *temp;

	while (lex)
	{
		temp = lex;
		lex = lex->next;
		free(temp->value);
		free(temp);
	}
}

void add_operator(t_lexer **lex, char *line, size_t *end)
{
	size_t len;

	len = 0;
	while (line[len] && is_operator_char(line[len]) && line[0] == line[len] && len < 2)
	{
		len++;
		if (line[0] == '|')
			break ;
	}
	new_lexer(lex, line, len); // TODO: check return
	(*end) += len;
}

void	print_lexer(t_lexer *lex)
{
	while (lex)
	{
		printf("value: %s\n", lex->value);
		printf("type: %d\n\n", lex->type);
		lex = lex->next;
	}
}

int	add_quoted_word(t_lexer **lex, char *line, size_t *end)
{
	size_t	len;
	char	quote;

	quote = line[0];
	len = 1;
	while (line[len] && line[len] != quote)
		len++;
	if (len > 1)
		new_lexer(lex, line, len); // TODO: check return
	if (line[len] == quote)
		len++;
	(*end) += len;
	return (0);
}

int	lexer_director(t_lexer **lex, size_t *end, size_t *start, char *line)
{
	while (line[*end])
	{
		if (line[*end] == '"' || line[*end] == '\'')
		{
			if (*end > *start)
				if (new_lexer(lex, line + *start, *end - *start)) // TODO: check return
					return (1);
			*start = *end;
			add_quoted_word(lex, line + *start, end); // TODO: check return
			*start = *end;
		}
		else
		{
			if (is_operator_char(line[*end]))
			{
				if (*end > *start)
					if (new_lexer(lex, line + *start, *end - *start))// TODO: check return
						return (1);
				*start = *end;
				while (line[*end] && is_operator_char(line[*end]))
				{
					add_operator(lex, line + *start, end); // TODO: check return
					*start = *end;
				}
			}
		}
		(*end)++;
	}
	return (0);
}

t_lexer	*lexer(char *line)
{
	t_lexer *lex;
	size_t	end;
	size_t	start;

	end = 0;
	start = 0;
	lex = NULL;
	if (lexer_director(&lex, &end, &start, line))
	{
		free_lexer(lex);
		return (NULL);
	}
	if (end > start)
		new_lexer(&lex, line + start, end - start); // TODO: check return
	return (lex);
}