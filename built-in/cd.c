/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 15:26:03 by arina             #+#    #+#             */
/*   Updated: 2025/09/04 16:43:10 by mabaghda         ###   ########.fr       */
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

void	update_env_new_and_old_pwd(t_env **env, char *old_pwd)
{
	char	*new_pwd;

	if (old_pwd)
		update_env_value(env, "OLDPWD", old_pwd);
	new_pwd = getcwd(NULL, 0);
	if (new_pwd)
	{
		update_env_value(env, "PWD", new_pwd);
		free(new_pwd);
	}
}

void	cd_command(t_data *data)
{
	char	*old_pwd;
	char	*target;

	old_pwd = get_env_value(data->env, "PWD");
	if (!data->stack->next)
		target = get_env_value(data->env, "HOME");
	else if (ft_strcmp(data->stack->next->string, "-") == 0)
		target = get_env_value(data->env, "OLDPWD");
	else
		target = data->stack->next->string;
	if (!target || chdir(target) != 0)
	{
		perror("minishell: cd");
		g_exit_status = 1;
		return ;
	}
	update_env_new_and_old_pwd(&data->env, old_pwd);
	g_exit_status = 0;
	if (data->stack->next->next)
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		// write (2, "minishell: cd: too many arguments", 34);
		g_exit_status = 1;
	}
	update_env_arr(data);
}
