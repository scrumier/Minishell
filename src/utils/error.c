/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scrumier <scrumier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:11:12 by scrumier          #+#    #+#             */
/*   Updated: 2024/08/14 10:42:19 by scrumier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** @brief: Print an error message and return the status
** @param msg The message
** @param new The new pipe
** @param old The old pipe
** @param cmd The command
** @return 1
*/
int	error_pipe(char *msg, int new[2], int old[2], t_cmd *cmd)
{
	(void)cmd;
	if (msg)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(msg, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	if (old[0])
		close(old[0]);
	if (old[1])
		close(old[1]);
	if (new[0])
		close(new[0]);
	if (new[1])
		close(new[1]);
	exit(1);
}

/*
** @brief: Print an error message and return the status
** @param mshell The minishell
** @param status The status
** @param msg The message
** @return The status
*/
int	error_cmd(t_minishell *mshell, int status, char *msg)
{
	mshell->last_exit_status = status;
	if (msg)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(msg, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	return (status);
}

/*
** @brief: Print an error message and return the status
** @param msg The message to print (nullable)
** @param ptr The pointer to free (nullable)
** @param ptr2 The pointer to free (nullable)
** @param ptr3 The pointer to free (nullable)
** @return 1
*/
int	error_msg_free(char *msg, void *ptr, void *ptr2, void *ptr3)
{
	if (msg)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(msg, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	if (ptr)
		free_null(ptr);
	if (ptr2)
		free_null(ptr2);
	if (ptr3)
		free_null(ptr3);
	return (EXIT_FAILURE);
}

int	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (EXIT_FAILURE);
	while (tab[i])
	{
		free_null(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free_null(tab);
	return (EXIT_SUCCESS);
}

int	error_msg(char *msg)
{
	if (msg)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(msg, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	return (EXIT_FAILURE);
}
