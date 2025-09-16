/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimanuk <arimanuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 18:10:55 by arimanuk          #+#    #+#             */
/*   Updated: 2025/09/14 17:45:06 by arimanuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	env_size(t_env *env)
{
	int	count;

	count = 0;
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

void	env_command(t_env *env, t_token *stack)
{
	if (stack->next && stack->next->type == WORD)
	{
		ft_putstr_fd("env: '", 2);
		ft_putstr_fd(stack->next->string, 2);
		ft_putstr_fd("': No such file or directory\n", 2);
		g_exit_status = 127;
		return ;
	}
	g_exit_status = 0;
	while (env)
	{
		if ((ft_strcmp(env->value, "") != 0) || (ft_strcmp(env->value, "") == 0
				&& env->flag == 1))
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}
