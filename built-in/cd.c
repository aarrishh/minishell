/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arina <arina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 15:26:03 by arina             #+#    #+#             */
/*   Updated: 2025/09/02 21:49:43 by arina            ###   ########.fr       */
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

char	*change_tsilda_to_home(char *str, t_env *env)
{
	char	*home;
	char	*target;
	char	*result;

	home = ft_strdup(ft_strchr(str, '/'));
	target = get_env_value(env, "HOME");
	result = ft_strjoin(target, home);
	free(home);
	return (result);
}

void	cd_command(t_token *stack, t_env **env)
{
	char	*old_pwd;
	char	*target;

	old_pwd = get_env_value(*env, "PWD");
	if (!stack->next)
		target = get_env_value(*env, "HOME");
	else if (ft_strcmp(stack->next->string, "-") == 0 \
		|| ft_strcmp(stack->next->string, "~") == 0)
		target = get_env_value(*env, "OLDPWD");
	else if (ft_strcmp(stack->next->string, "~") >= 0)
		target = change_tsilda_to_home(stack->next->string, *env);
	else
		target = stack->next->string;
	if (!target || chdir(target) != 0)
	{
		perror("minishell: cd");
		g_exit_status = 1;
		return ;
	}
	update_env_new_and_old_pwd(env, old_pwd);
	g_exit_status = 0;
	if (stack->next->next)
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		g_exit_status = 1;
	}
}



