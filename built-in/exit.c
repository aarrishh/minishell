/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arina <arina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 15:23:54 by arina             #+#    #+#             */
/*   Updated: 2025/08/09 07:10:59 by arina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exit_command_print_function(t_token *tmp, long long num)
{
	if (tmp->next)
		return (printf("exit\nminishell: exit: too many arguments\n"), 1);
	else
	{
		printf("exit\n"),
		exit(num % 256);
	}
	return (0);
}

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
			printf("exit\nminishell: exit: %s: numeric argument required\n", \
			tmp->string);
			exit(2);
		}
	}
	if (exit_command_print_function(tmp, num) == 1)
		return (1);
	return (0);
}
