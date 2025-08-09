/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 18:10:55 by arimanuk          #+#    #+#             */
/*   Updated: 2025/08/09 17:56:14 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_add_back(t_env *node, t_env **head)
{
	t_env	*tmp;

	if (*head == NULL)
	{
		*head = node;
		return ;
	}
	tmp = *head;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = node;
}

t_env	*new_node(char *key, char *value)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	new_node->key = key;
	new_node->value = value;
	new_node->flag = 0;
	new_node->next = NULL;
	return (new_node);
}

int	find_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

t_env	*add_env_to_list(char **envp)
{
	t_env	*env;
	t_env	*cur_node;
	char	*str;
	int		i;

	i = 0;
	str = NULL;
	env = NULL;
	while (envp[i])
	{
		str = ft_strdup(envp[i]);
		cur_node = new_node(ft_substr(str, 0, find_equal(str)), \
		ft_strdup(ft_strchr(str, '=') + 1));
		env_add_back(cur_node, &env);
		i++;
	}
	return (env);
}

void	env_command(t_env *env)
{
	while (env)
	{
		if ((ft_strcmp(env->value, "") != 0)
			|| (ft_strcmp(env->value, "") == 0 && env->flag == 1))
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}
