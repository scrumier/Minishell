/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtasi <mwojtasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 05:31:43 by mwojtasi          #+#    #+#             */
/*   Updated: 2024/05/07 17:42:28 by mwojtasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse(t_minishell *mshell)
{
	size_t	i;
	char 	**split;

	i = 0;
	split = ft_split(mshell->line, '|');
		if (!split)
			return (-1);
	while (mshell->line[i])
	{
		
	}
	return (0);
}