/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arina <arina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:50:14 by arina             #+#    #+#             */
/*   Updated: 2025/07/28 20:04:00 by arina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	n_check(char *str)
{
	int	i;

	if (str[0] != '-' || str[1] != 'n')
		return (-1);
	i = 2;
	while (str[i])
	{
		if (str[i] != 'n')
			return (-1);
		i++;
	}
	return (0);
}


void	*echo_command(t_token **stack)
{
	t_token *tmp;
	int	flag;

	flag = 0;
	if (!(*stack)->next)
		return(printf("\n"), "");
	tmp = (*stack)->next;
	while (tmp && ft_strncmp(tmp->string, "-n", 2) == 0)
	{
		flag = 1;
		if (n_check(tmp->string) == -1)
		{	
			flag = 0;
			break ;
		}
		else
			tmp = tmp->next;
	}
	// printf("flag->%d\n", flag);
	while (tmp && tmp->next)
	{
		printf("%s ", tmp->string);
		tmp = tmp->next;
	}
	if (tmp)
	{
		if (flag == 1)
			printf("%s", tmp->string);
		else
			printf("%s\n", tmp->string);
	}
	return ("");
}

void	exit_command(t_token **stack)
{
	t_token	*tmp;
	int	num;
	
	num = 0;
	tmp = (*stack);
	if (tmp->next)
	{
		tmp = tmp->next;
		num = ft_atoi(tmp->string);
		if (num == 0)
		printf("error\n");
	}
	if (tmp->next)
		printf("exit: too many arguments\n");
	else
	{
		printf("exit\n");
		exit(num % 256);
	}
}

void	built_in_functions(t_token **stack)
{
	if (ft_strcmp((*stack)->string, "echo") == 0)
		echo_command(stack);
	else if (ft_strcmp((*stack)->string, "exit") == 0)
		exit_command(stack);
	else
		printf("%s: command not found\n", ((*stack)->string));
}