/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scrumier <scrumier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:15:47 by scrumier          #+#    #+#             */
/*   Updated: 2024/08/16 13:35:36 by scrumier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

void		close_and_cpy(int old[2], int new[2], int i);
void		close_free(t_minishell *mshell, int old[2], int new[2]);
int			error_pipe(char *msg, int new[2], int old[2], t_cmd *cmd);
int			error_cmd(t_minishell *mshell, int status, char *msg);
int			error_msg_free(char *msg, void *ptr, void *ptr2, void *ptr3);
long		ft_atoi(const char *str);
char		*tmp_file(int nb);
int			free_tab(char **tab);
void		print_tab(char **tab);
bool		is_redir_before(t_cmd *cmd, char **redir, char **reference);
void		free_mshell(t_minishell *mshell);
void		print_tab(char **tab);
int			ft_tablen(char **tab);
int			put_in_env(char **args, size_t i, t_minishell *mshell);
size_t		ft_varlen(char *var, char c);
int			is_n_only_spaces(char *line, size_t size);
bool		isnumber(char *str);
int			lst_size(t_cmd *cmd);
void		reset_fds(t_minishell *mshell, int old[2], int new[2]);
void		reset_default_fd(t_minishell *mshell);
int			set_default_fd(t_minishell *mshell, int old[2], int new[2]);
void		reset_fds(t_minishell *mshell, int old[2], int new[2]);
uint8_t		atoutint8(const char *str, bool *is_overflow);
long long	ft_atol_overflow(const char *str, bool *is_overflow);
int			error_msg(char *msg);
void		close_old(int i, int old[2]);
void		if_is_directory(t_cmd *cmd, t_minishell *mshell, int i, char *tmp);
void		init(t_minishell *mshell);
void		add_slash_cd(char *path);
void		init_fds(t_fds *fds, int old[2], int new[2]);
int			is_directory(struct stat *buf, t_cmd *cmd, \
			t_minishell *mshell, int i);
void		set_sig_and_exit_status(t_minishell *mshell);

#endif