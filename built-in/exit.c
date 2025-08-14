/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 15:23:54 by arina             #+#    #+#             */
/*   Updated: 2025/08/14 11:23:48 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exit_command_print_function(t_token *tmp, long long num)
{
	if (tmp->next)
		return (printf("exit\nminishell: exit: too many arguments\n"), 1);
	else
	{
		printf("exit\n"), exit(num % 256);
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
			printf("exit\nminishell: exit: %s: numeric argument required\n",
				tmp->string);
			// free_all(env, stack, split);
			exit(2);
		}
	}
	if (exit_command_print_function(tmp, num) == 1)
		return (1);
	return (0);
}
