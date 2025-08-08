/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arina <arina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 15:23:54 by arina             #+#    #+#             */
/*   Updated: 2025/08/08 17:10:09 by arina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exit_command(t_token **stack)
{
	t_token		*tmp;
	long long	num;
	int			flag;

	num = 0;
	flag = 0;
	tmp = (*stack);
	if (tmp->next)
	{
		tmp = tmp->next;
		flag = ft_atol(tmp->string, &num);
		if (flag == -1)
		{
			printf("exit\nbash: exit: %s: numeric argument required\n", \
			tmp->string);
			exit(2);
		}
	}
	if (tmp->next)
		return (printf("exit\nbash: exit: too many arguments\n"), 1);
	else
	{
		printf("exit\n"),
		exit(num % 256);
	}
	return (0);
}
