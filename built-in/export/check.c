/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 15:30:26 by arina             #+#    #+#             */
/*   Updated: 2025/09/04 17:32:19 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_sameness(char *str, t_env *env)
{
	char	*sub;

	while (env)
	{
		sub = ft_substr(str, 0, find_equal(str));
		if (ft_strcmp(sub, "_") == 0)
			return (free(sub), 0);
		else if (ft_strcmp(sub, env->key) == 0)
			return (free(sub), 1);
		free(sub);
		if ((find_equal_for_export(str) == -2))
		{
			sub = ft_substr(str, 0, find_plus(str));
			if (ft_strcmp(sub, env->key) == 0)
				return (free(sub), 2);
			free(sub);
		}
		env = env->next;
	}
	return (0);
}


void	check_i_have_value_after_equal_symbol(int index,
			char *str, t_env **node)
{
	char	*sub;

	sub = ft_substr(str, 0, find_equal(str));
	if (ft_strcmp(sub, (*node)->key) == 0)
	{
		if (str[index + 1] == '\0')
			(*node)->flag = 1;
	}
	free(sub);
}


void	check_i_have_value_after_equal_symbol_version_two(int index,
			char *str, t_env **env)
{
	t_env	*tmp;
	char	*sub;

	tmp = *env;
	while (tmp)
	{
		sub = ft_substr(str, 0, find_equal(str));
		if (ft_strcmp(sub, tmp->key) == 0)
		{
			if (str[index + 1] == '\0')
				tmp->flag = 1;
			else
				tmp->flag = 0;
			free(sub);
			return ;
		}
		free(sub);
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
