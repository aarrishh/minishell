/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 15:50:18 by mabaghda          #+#    #+#             */
/*   Updated: 2025/08/09 17:06:25 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*find_path(t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "$PATH"))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*split_path(t_env **env, char *cmd)
{
	int i;
	t_env *path;
	char **splitted_path;
	char *idk;

	i = 0;
	path = find_path(env);
	splitted_path = ft_split(path->value, ':');
	while (splitted_path[i])
	{
		idk = ft_strjoin(splitted_path[i], "/");
		idk = ft_strjoin(idk, cmd);
		if (access(idk, X_OK) == 0)
			return (idk);
		free(idk);
		i++;
	}
	return (NULL);
}