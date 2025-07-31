/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 18:09:07 by mabaghda          #+#    #+#             */
/*   Updated: 2025/07/31 18:36:08 by mabaghda         ###   ########.fr       */
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

t_env	*env_last(t_env *env_list)
{
	if (!env_list)
		return (NULL);
	while (env_list->next)
		env_list = env_list->next;
	return (env_list);
}

void	add_env_node(t_env **env_list, t_env *new)
{
	t_env	*last;

	last = env_last(*env_list);
	if (!last)
		*env_list = new;
	else
		last->next = new;
}

t_env	*new_env_node(void *key, char **value)
{
	t_env	*new;
	int		i;
	char	*tmp;

	i = 1;
	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = key;
	new->value = ft_strdup("");
	while (value[i])
	{
		tmp = ft_strjoin(new->value, value[i]);
		free(new->value);
		new->value = tmp;
		if (value[i + 1])
		{
			tmp = ft_strjoin(new->value, "=");
			free(new->value);
			new->value = tmp;
		}
		i++;
	}
	new->next = NULL;
	return (new);
}

void	separate_key_and_value(char *env_var, t_env **env_struct)
{
	char	**splitted_var;
	t_env	*new;

	splitted_var = ft_split(env_var, '=');
	if (!splitted_var)
		return ;
	new = new_env_node(splitted_var[0], splitted_var);
	if (!new)
		return ;
	add_env_node(env_struct, new);
}

void	chgitem_env(char **env, t_env **env_struct)
{
	int		i;
	int		j;
	char	**new_env;
	// t_env	*tmp;

	i = 0;
	j = 0;
	new_env = copy_env(env);
	while (env[i])
	{
		separate_key_and_value(new_env[i], env_struct);
		i++;
	}
	// tmp = *env_struct;
	// while (tmp->next)
	// {
	// 	printf("key-%s\n", tmp->key);
	// 	printf("value-%s\n", tmp->value);
	// 	tmp = tmp->next;
	// }
}
