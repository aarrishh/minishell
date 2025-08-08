/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arina <arina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 15:35:34 by arina             #+#    #+#             */
/*   Updated: 2025/08/08 19:12:17 by arina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_error_export(char *str)
{
	printf("bash: export: `%s': not a valid identifier\n", str);
}

void	print_export(t_env *env)
{
	t_env *tmp;

	tmp = sort_env(env);
	while (tmp)
	{
		if (ft_strcmp(tmp->value, "") == 0 && tmp->flag == 0)
			printf("declare -x %s\n", tmp->key);
		else
			printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}
