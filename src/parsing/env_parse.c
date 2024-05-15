/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtasi <mwojtasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:40:14 by mwojtasi          #+#    #+#             */
/*   Updated: 2024/05/15 19:23:04 by mwojtasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parse_path(t_minishell *mshell, char *env)
{
	char	*path;

	path = ft_strdup(env + 5);
	if (!path)
		return (1); // TODO: add a free struct
	mshell->path = ft_split(path, ':');
	if (!mshell->path)
		return (1); // TODO: add a free struct
	free(path);
	return (0);
}

static int	set_sysbin(t_minishell *mshell)
{
	mshell->path = malloc(sizeof(char *) * 2);
	if (!mshell->path)
		return (1); // TODO: add a free struct
	mshell->path[0] = ft_strdup("/bin");
	if (!mshell->path[0])
		return (1); // TODO: add a free struct
	mshell->path[1] = NULL;
	return (0);
}

int	save_path(t_minishell *mshell, char **env)
{
	size_t	i;

	i = 0;
	if (!env || !env[0])
		set_sysbin(mshell);
	else
	{
		while (env[i])
		{
			if (ft_strncmp(env[i], "PATH=", 5) == 0)
			{
				if (env[i][5] == 0)
					set_sysbin(mshell);
				else
					parse_path(mshell, env[i]);
				return (0);
			}
			i++;
		}
	}
	if (!mshell->path)
		set_sysbin(mshell);
	return (0);
}