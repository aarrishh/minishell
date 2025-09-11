/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arina <arina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 15:39:22 by arina             #+#    #+#             */
/*   Updated: 2025/09/10 20:38:49 by arina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	sort_env_part_two(t_env **env, t_env **idk)
{
	char	*temp;
	int		flag_tmp;

	temp = (*env)->key;
	(*env)->key = (*idk)->key;
	(*idk)->key = temp;
	temp = (*env)->value;
	(*env)->value = (*idk)->value;
	(*idk)->value = temp;
	flag_tmp = (*env)->flag;
	(*env)->flag = (*idk)->flag;
	(*idk)->flag = flag_tmp;
}

t_env	*sort_env(t_env *env)
{
	t_env	*idk;
	t_env	*tmp;

	tmp = env;
	while (env && env->next)
	{
		idk = env->next;
		while (idk)
		{
			if (ft_strcmp(env->key, idk->key) > 0)
				sort_env_part_two(&env, &idk);
			idk = idk->next;
		}
		env = env->next;
	}
	return (tmp);
}

void	change_value(char *str, t_env **env)
{
	t_env	*tmp;
	char	*key;

	tmp = *env;
	key = ft_substr(str, 0, find_equal(str));
	while (tmp)
	{
		if (ft_strcmp(key, tmp->key) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(ft_strchr(str, '=') + 1);
			break ;
		}
		tmp = tmp->next;
	}
	free(key);
}

void	change_value_for_plus_equal_case(char *str, t_env **env)
{
	t_env	*tmp;
	char	*key;
	char	*idk;
	char	*new_value;

	key = ft_substr(str, 0, find_plus(str));
	idk = ft_strchr(str, '=') + 1;
	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(key, tmp->key) == 0)
		{
			new_value = ft_strjoin(tmp->value, idk);
			free(tmp->value);
			tmp->value = new_value;
			break ;
		}
		tmp = tmp->next;
	}
	free(key);
}
