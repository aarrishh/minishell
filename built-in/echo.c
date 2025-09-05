/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arina <arina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 15:20:52 by arina             #+#    #+#             */
/*   Updated: 2025/09/05 17:14:41 by arina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	tpelu_pahna(t_token *tmp, int flag)
{
	g_exit_status = 0;
	if (tmp)
	{
		if (flag == 1)
			printf("%s", tmp->string);
		else
			printf("%s\n", tmp->string);
	}
}

void	*echo_command(t_token **stack)
{
	t_token	*tmp;
	int		flag;

	flag = 0;
	if (!(*stack)->next || (*stack)->next->type != WORD)
		return (printf("\n"), "");
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
	while (tmp && tmp->next && tmp->next->type == WORD)
	{
		printf("%s ", tmp->string);
		tmp = tmp->next;
	}
	tpelu_pahna(tmp, flag);
	return ("");
}
