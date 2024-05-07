/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtasi <mwojtasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 03:19:56 by mwojtasi          #+#    #+#             */
/*   Updated: 2024/05/07 17:47:47 by mwojtasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	t_minishell mshell;

	(void)argc;
	(void)argv;
	
	mshell.env = envp;
	while (42)
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
