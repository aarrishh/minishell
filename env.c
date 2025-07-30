/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 18:09:07 by mabaghda          #+#    #+#             */
/*   Updated: 2025/07/30 19:27:26 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_env_size(char **env)
{
	int	len;

	len = 0;
	while (env[len])
	{
		len++;
	}
	return (len);
}

char	**copy_env(char **env)
{
	int		len;
	int		i;
	char	**cp_env;

	i = 0;
	len = count_env_size(env);
	cp_env = (char **)malloc(sizeof(char *) * (len + 1));
	if (!cp_env)
		return (NULL);
	while (env[i])
	{
		cp_env[i] = ft_strdup(env[i]);
		i++;
	}
	return (cp_env);
}

// void	separate_key_and_value(char *env_var)
// {
// 	;
// }

void	print_env(char **env)
{
	int i;
	int j;
	char **new_env;

	i = 0;
	j = 0;
	new_env = copy_env(env);
	// separate_key_and_value(new_env[i]);
	// while (new_env[i])
	// {
	// 	while (new_env[i][j])
	// 	{
	// 		printf("%c", new_env[i][j]);
	// 		j++;
	// 	}
	// 	printf("\n");
	// 	i++;
	// }
}