/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 19:31:18 by arina             #+#    #+#             */
/*   Updated: 2025/09/18 11:34:00 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_cd_error(char *target)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(target, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

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

void	update_env_new_and_old_pwd(t_env **env, char *old_pwd, char **target,
		int flag)
{
	char	*new_pwd;

	if (flag == 1)
		free(*target);
	(void)target;
	if (old_pwd)
		update_env_value(env, "OLDPWD", old_pwd);
	new_pwd = getcwd(NULL, 0);
	if (new_pwd)
	{
		update_env_value(env, "PWD", new_pwd);
		free(new_pwd);
	}
}
