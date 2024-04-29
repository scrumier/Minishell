/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtasi <mwojtasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 03:19:56 by mwojtasi          #+#    #+#             */
/*   Updated: 2024/04/29 05:43:12 by mwojtasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/libft.h"
int main(int argc, char **argv, char **envp)
{
	t_minishell mshell;

	(void)argc;
	(void)argv;
	
	mshell.env = envp;
	while (1)
	{
		mshell.line = readline("minishell$ ");
		if (!mshell.line)
			break ;
		if (*mshell.line)
			add_history(mshell.line);
		parse(&mshell);
		free(mshell.line);
	}
}