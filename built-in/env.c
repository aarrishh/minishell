/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimanuk <arimanuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 18:10:55 by arimanuk          #+#    #+#             */
/*   Updated: 2025/08/21 15:46:02 by arimanuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	env_size(t_env *env)
{
	int count = 0;

	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

char	*join_key_value(char *key, char *value)
{
	int		len;
	char	*str;

	if (!value)
		value = "";
	len = ft_strlen(key) + 1 + ft_strlen(value) + 1;
	str = malloc(len);
	if (!str)
		return (NULL);
	ft_strcpy(str, key);
	ft_strcat(str, "=");
	ft_strcat(str, value);
	return (str);
}

char	**env_to_envp(t_env *env)
{
	char	**envp;
	int		i;

	envp = malloc(sizeof(char *) * (env_size(env) + 1));
	if (!envp)
		return (NULL);
	i = 0;
	while (env)
	{
		envp[i] = join_key_value(env->key, env->value);
		if (!envp[i])
		{
			while (i > 0)
				free(envp[--i]);
			free(envp);
			return (NULL);
		}
		i++;
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}


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
		free(str);
		env_add_back(cur_node, &env);
		i++;
	}
	return (env);
}

void	add_env_value(t_env **env, char *key, char *value)
{
	t_env	*tmp;
	t_env	*node;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return ;
		}
		tmp = tmp->next;
	}
	node = new_node(ft_strdup(key), ft_strdup(value));
	env_add_back(node, env);
}

void	env_command(t_env *env, t_token *stack)
{
	if (stack->next && stack->next->type == WORD)
	{
		printf("env: '%s': No such file or directory\n", stack->next->string);
		g_exit_status = 127;
		return ;
	}
	g_exit_status = 0;
	while (env)
	{
		if ((ft_strcmp(env->value, "") != 0)
			|| (ft_strcmp(env->value, "") == 0 && env->flag == 1))
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}
