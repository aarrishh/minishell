/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimanuk <arimanuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 15:23:54 by arina             #+#    #+#             */
/*   Updated: 2025/08/23 17:35:43 by arimanuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exit_command_print_function(t_token *tmp, long long num)
{
	if (tmp->next)
	{
		g_exit_status = 1;
		return (printf("exit\nminishell: exit: too many arguments\n"), 1);
	}
	else
	{
		printf("exit\n"),
		g_exit_status = num % 256;
		rl_clear_history();
		exit(num % 256);
	}
	return (0);
}

int	exit_command(t_token **stack, t_env **env, char **split)
{
	t_token		*tmp;
	long long	num;
	int			flag;

	(void)split;
	(void)env;
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
			g_exit_status = 2;
			free_all(env, stack, &split);
			rl_clear_history();
			exit(2);
		}
	}
	if (exit_command_print_function(tmp, num) == 1)
	{
		g_exit_status = 1;
		return (1);
	}
	return (0);
}
