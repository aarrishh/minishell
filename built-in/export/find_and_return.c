/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_and_return.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arina <arina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 15:33:37 by arina             #+#    #+#             */
/*   Updated: 2025/08/08 20:38:42 by arina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	find_equal_for_export(char *str)
{
	int	i;

	i = 0;
	if (find_plus_equal(str) != -1)
		return (-2);
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int	find_plus_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i + 1])
	{
		if (str[i] == '+' && str[i + 1] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int	find_plus(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '+')
			return (i);
		i++;
	}
	return (-1);
}
