/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scrumier <scrumier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:15:47 by scrumier          #+#    #+#             */
/*   Updated: 2024/05/17 12:20:21 by scrumier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

int	error_pipe(char *msg, int new[2], int old[2], t_cmd *cmd);
int	error_cmd(t_minishell *mshell, int status, char *msg);

#endif