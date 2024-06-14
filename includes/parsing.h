/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtasi <mwojtasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:01:12 by scrumier          #+#    #+#             */
/*   Updated: 2024/06/14 17:43:11 by mwojtasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

struct s_lexer
{
	char			*value;
	bool			space_after;
	t_token_type	type;
	t_lexer			*next;
	t_lexer			*prev;
};

int		parse(t_minishell *mshell);
char	**ft_split_args(char const *str, char sep);
char	*copy_str(const char *str, size_t start, size_t len);
int		is_in_quote(char c, char *in_quote);
void	free_str(char **split);
char	**init_split(size_t count);
t_lexer	*lexer(char *line);
void	print_lexer(t_lexer *lex);
int		validate(t_lexer *lex);
int	new_lexer(t_lexer **lex, char *line, size_t size);
int	save_path(t_minishell *mshell, char **env);
t_cmd	*lexer_to_cmd(t_lexer *lex, char **path);
t_lexer	*get_last_lexer(t_lexer *lex);
int		get_cmd_path(t_cmd **cmd, char **path);
int		expand(t_lexer **lex, char **envp, int last_exit_status);
t_cmd	*delete_cmd(t_cmd **cmd, t_cmd *to_delete);
t_lexer	*delete_lexer(t_lexer **lex, t_lexer *to_delete);
void	allocate_env(t_minishell *mshell, char **envp);
void	print_cmd(t_cmd *cmd);
void	print_cmds(t_cmd *cmd);
#endif