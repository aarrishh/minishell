/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arina <arina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 15:30:26 by arina             #+#    #+#             */
/*   Updated: 2025/08/08 20:43:04 by arina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_sameness(char *str, t_env *env)
{
	while (env)
	{
		if (ft_strcmp(ft_substr(str, 0, find_equal(str)), "_") == 0)
			return (0);
		else if (ft_strcmp(ft_substr(str, 0, find_equal(str)), env->key) == 0)
			return (1);
		else if ((find_equal_for_export(str) == -2)
			&& ft_strcmp(ft_substr(str, 0, find_plus(str)), env->key) == 0)
			return (2);
		env = env->next;
	}
	return (0);
}

void	check_i_have_value_after_equal_symbol(int index,
			char *str, t_env **node)
{
	if (ft_strcmp(ft_substr(str, 0, find_equal(str)), (*node)->key) == 0)
	{
		if (str[index + 1] == '\0')
			(*node)->flag = 1;
		return ;
	}
}

void	check_i_have_value_after_equal_symbol_version_two(int index,
			char *str, t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(ft_substr(str, 0, find_equal(str)), tmp->key) == 0)
		{
			if (str[index + 1] == '\0')
				tmp->flag = 1;
			else
				tmp->flag = 0;
			return ;
		}
		tmp = tmp->next;
	}
}

int	check_key(char *key)
{
	int	i;

	i = 0;
	if (ft_strcmp(key, "_") == 0)
		return (-1);
	if (!ft_isalpha(key[0]) && key[0] != '_')
		return (-2);
	while (key[i] && (key[i] != '=' && !(key[i] == '+' && key[i + 1] == '=')))
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (-2);
		i++;
	}
	return (0);
}
