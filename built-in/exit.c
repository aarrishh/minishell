/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arina <arina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 15:23:54 by arina             #+#    #+#             */
/*   Updated: 2025/08/29 19:09:17 by arina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exit_command_print_function(t_token *tmp, long long num)
{
	if (tmp->next)
	{
		g_exit_status = 127;
		return (ft_putendl_fd("exit\nminishell: exit: too many arguments", 2), 1);
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
			write (2, "exit\nminishell: exit: ", 23);
			write (2, &tmp->string, ft_strlen(tmp->string));
			write (2, ": numeric argument required\n", 29);
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
