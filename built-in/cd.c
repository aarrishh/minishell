/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 15:26:03 by arina             #+#    #+#             */
/*   Updated: 2025/08/19 17:59:16 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_value(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	update_env_value(t_env **env, char *key, char *update_value)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(key, tmp->key) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(update_value);
			break ;
		}
		tmp = tmp->next;
	}
}

void	cd_command(t_token *stack, t_env **env)
{
	char	*old_pwd;
	char	*new_pwd;

	old_pwd = get_env_value(*env, "PWD");
	if (chdir(stack->next->string) != 0)
	{
		perror("minishell: cd");
		g_exit_status = 1;
		return ;
	}
	if (old_pwd)
		update_env_value(env, "OLDPWD", old_pwd);
	new_pwd = getcwd(NULL, 0);
	if (new_pwd)
	{
		update_env_value(env, "PWD", new_pwd);
		free(new_pwd);
	}
}
