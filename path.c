/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimanuk <arimanuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 15:50:18 by mabaghda          #+#    #+#             */
/*   Updated: 2025/08/11 17:33:34 by arimanuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*find_path(t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "PATH") == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*split_path(t_env **env, char *cmd)
{
	int		i;
	t_env	*path;
	char	**splitted_path;
	char	*idk;
	char	*tmp;

	path = find_path(env);
	if (!path)
		return (NULL);
	splitted_path = ft_split(path->value, ':');
	i = 0;
	while (splitted_path[i])
	{
		idk = ft_strjoin(splitted_path[i], "/");
		tmp = ft_strjoin(idk, cmd);
		free(idk);
		idk = tmp;
		if (access(idk, X_OK) == 0)
		{
			free_array(splitted_path);
			return (idk);
		}
		free(idk);
		i++;
	}
	free_array(splitted_path);
	printf("%s: command not found\n", cmd);
	return (NULL);
}
