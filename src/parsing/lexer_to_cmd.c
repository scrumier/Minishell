/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_to_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtasi <mwojtasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:23:05 by mwojtasi          #+#    #+#             */
/*   Updated: 2024/06/19 19:54:20 by mwojtasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_type	token_to_cmd(t_token_type type)
{
	if (type == T_WORD)
		return (CMD);
	else if (type == T_PIPE)
		return (PIP);
	else if (type == T_REDIR_IN)
		return (RED_IN);
	else if (type == T_REDIR_OUT)
		return (RED_OUT);
	else if (type == T_APPEND_OUT)
		return (APP_OUT);
	else if (type == T_HERE_DOC)
		return (HDOC);
	return (CMD);
}

char	*cmd_type_to_str(t_cmd_type type)
{
	if (type == CMD)
		return ("CMD");
	else if (type == PIP)
		return ("PIP");
	else if (type == RED_IN)
		return ("RED_IN");
	else if (type == RED_OUT)
		return ("RED_OUT");
	else if (type == APP_OUT)
		return ("APP_OUT");
	else if (type == HDOC)
		return ("HDOC");
	return ("UNDEFINED");
}

void	free_cmd(t_cmd *cmd)
{
	if (cmd->cmd)
		free(cmd->cmd);
	if (cmd->args)
	{
		for (int i = 0; cmd->args[i]; i++)
			free(cmd->args[i]);
		free(cmd->args);
	}
	if (cmd->infile)
	{
		for (int i = 0; cmd->infile[i]; i++)
			free(cmd->infile[i]);
		free(cmd->infile);
	}
	if (cmd->outfile)
	{
		for (int i = 0; cmd->outfile[i]; i++)
			free(cmd->outfile[i]);
		free(cmd->outfile);
	}
	free(cmd);
}

t_cmd	*new_cmd(char **args)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	if (args)
	{
		new->args = args;
		new->cmd = args[0];
	}
	else
	{
		new->args = NULL;
		new->cmd = NULL;
		new->is_valid_cmd = false;
	}
	new->infile = NULL;
	new->op_type[0] = UNDEFINED;
	new->outfile = NULL;
	new->op_type[1] = UNDEFINED;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

int	append_cmd(t_cmd **cmd, t_cmd *new)
{
	t_cmd	*tmp;

	if (*cmd == NULL)
	{
		*cmd = new;
		(*cmd)->prev = NULL;
	}
	else
	{
		tmp = *cmd;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
	return (0);
}

t_cmd	*get_last_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	if (!tmp)
		return (NULL);
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

size_t	get_cmd_size(t_lexer *lex)
{
	size_t	size;

	size = 0;
	while (lex)
	{
		if (lex->value && (lex->type == T_WORD || lex->type == T_S_QUOTED_WORD
			|| lex->type == T_D_QUOTED_WORD))
			size += ft_strlen(lex->value) + 1;
		lex = lex->next;
	}
	return (size);
}

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

t_cmd_type get_op_type(t_lexer *lex)
{
	if (!lex)
		return (CMD);
	else
		return (token_to_cmd(lex->type));
}

void	print_cmds(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		print_cmd(tmp);
		tmp = tmp->next;
	}
}

void	print_cmd(t_cmd *cmd)
{
	printf("cmd: %s\n", cmd->cmd);
	printf("args: ");
	if (cmd->args)
	{
		for (int i = 0; cmd->args[i]; i++)
			printf("%s, ", cmd->args[i]);
	}
	else
		printf("(null)");
	printf("\ninfile op type: %s\n", cmd_type_to_str(cmd->op_type[0]));
	printf("outfile op type: %s\n", cmd_type_to_str(cmd->op_type[1]));
	if (cmd->op_type[0] != UNDEFINED)
	{
		printf("infile: ");
		for (int i = 0; cmd->infile[i]; i++)
			printf("%s , ", cmd->infile[i]);
		printf("\n");
	}
	if (cmd->op_type[1] != UNDEFINED)
	{
		printf("outfile: ");
		for (int i = 0; cmd->outfile[i]; i++)
			printf("%s , ", cmd->outfile[i]);
		printf("\n");
	
	}
	printf("\n");
	(void)cmd;
}

int	append_redir(t_cmd *cmd, t_lexer **lex)
{
	if ((*lex)->type == T_REDIR_IN)
	{
		(*lex) = (*lex)->next;
		cmd->op_type[0] = RED_IN;
		ft_append_str(&(cmd->infile), (*lex)->value);
	}
	else if ((*lex)->type == T_REDIR_OUT)
	{
		(*lex) = (*lex)->next;
		cmd->op_type[1] = RED_OUT;
		ft_append_str(&(cmd->outfile), (*lex)->value);
	}
	else if ((*lex)->type == T_APPEND_OUT)
	{
		(*lex) = (*lex)->next;
		cmd->op_type[1] = APP_OUT;
		ft_append_str(&(cmd->outfile), (*lex)->value);
	}
	else if ((*lex)->type == T_HERE_DOC)
	{
		(*lex) = (*lex)->next;
		cmd->op_type[0] = HDOC;
		ft_append_str(&(cmd->infile), (*lex)->value);
	}
	return (0);	
}

bool	is_nospace_addable(t_token_type type)
{
	if (type == T_WORD || type == T_S_QUOTED_WORD || type == T_D_QUOTED_WORD)
		return (true);
	return (false);
}

int	nospace_add(char **args, t_lexer **lex)
{
	size_t	size;
	t_lexer *start;

	size = 0;
	start = *lex;
	while (*lex && (*lex)->value && (!size || (!(*lex)->prev->space_after)) && is_nospace_addable((*lex)->type))
	{
		size += ft_strlen((*lex)->value) + 1;
		*lex = (*lex)->next;
	}
	*lex = start;
	*args = ft_calloc(size + 1, sizeof(char));
	if (!*args)
		return (1);
	while (*lex && (*lex)->value && !(*lex)->space_after && is_nospace_addable((*lex)->type))
	{
		ft_strlcat(*args, (*lex)->value, size + 1);
		*lex = (*lex)->next;
	}
	if (*lex && (*lex)->value)
		ft_strlcat(*args, (*lex)->value, size + 1);
	return (0);
}

int	append_cmds(t_cmd **cmd, t_lexer **lex)
{
	// need to add system to not add paths for redirections
	char	**args;
	char	**args_start;
	t_cmd	*last_cmd;

	args = ft_calloc(get_word_num(*lex) + 1, sizeof(char *));
	args_start = args;
	if (!args)
		return (1);
	last_cmd = new_cmd(NULL); // TODO: check return
	append_cmd(cmd, last_cmd);
	while (*lex)
	{
		if ((*lex)->type == T_REDIR_IN || (*lex)->type == T_REDIR_OUT
			|| (*lex)->type == T_APPEND_OUT || (*lex)->type == T_HERE_DOC)
			append_redir(last_cmd, lex);
		else if ((*lex)->value && is_nospace_addable((*lex)->type))
		{
			if (!(*lex)->space_after && (*lex)->next && is_nospace_addable((*lex)->next->type))
			{
				if (nospace_add(args, lex))
					return (1);
			}
			else
				*args = ft_strdup((*lex)->value);
			args++;
		}
		else
			break ;
		if (*lex)
			*lex = (*lex)->next;
	}
	last_cmd->args = args_start;
	if (*args_start)
		last_cmd->cmd = ft_strdup(args_start[0]);
	else
	{
		last_cmd->cmd = NULL;
		last_cmd->args = NULL;
		last_cmd->is_valid_cmd = true;
	}
	return (0);
}

t_cmd	*delete_cmd(t_cmd **cmd, t_cmd *to_delete)
{
	t_cmd	*tmp;
	t_cmd	*next;
	
	tmp = *cmd;
	if (*cmd == to_delete)
	{
		*cmd = to_delete->next;
		if (*cmd)
			(*cmd)->prev = NULL;
		free_cmd(to_delete);
		return (*cmd);
	}
	while (tmp && tmp != to_delete)
		tmp = tmp->next;
	if (tmp && tmp == to_delete)
	{
		if (tmp->prev)
			tmp->prev->next = tmp->next;
		if (tmp->next)
			tmp->next->prev = tmp->prev;
		next = tmp->next;
		free_cmd(tmp);
		return (next);
	}
	return (NULL);
}

int	resolve_cmd_path(t_cmd **cmd, char **path, int *exit_status)
{
	t_cmd	*tmp;

	tmp = *cmd;
	while (tmp)
	{
		if (!tmp->cmd && tmp->is_valid_cmd)
		{
			tmp = tmp->next;
			continue ;
		}
		get_cmd_path(&tmp, path, exit_status);
		if (!tmp->is_valid_cmd)
		{
			tmp = delete_cmd(cmd, tmp);
			continue ;
		}
		tmp = tmp->next;
	}
	return (0);
}

t_cmd	*lexer_to_cmd(t_lexer *lex, char **path, int *exit_status)
{
	t_cmd	*cmd;
	t_lexer	*current_lex;

	cmd = NULL;
	current_lex = lex;
	while (current_lex)
	{
		append_cmds(&cmd, &current_lex);
		if (current_lex)
			current_lex = current_lex->next;
	}
	resolve_cmd_path(&cmd, path, exit_status);
	return (cmd);
}
