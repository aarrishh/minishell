/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimanuk <arimanuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 16:04:37 by arimanuk          #+#    #+#             */
/*   Updated: 2025/09/14 16:06:00 by arimanuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_syntax(t_token *stack)
{
	if (!stack)
		return (0);
	if (stack->type == PIPE)
	{
		ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
		return (-1);
	}
	while (stack)
	{
		if ((stack->type == REDIR_IN || stack->type == REDIR_OUT
				|| stack->type == APPEND || stack->type == HEREDOC)
			&& (!stack->next || stack->next->type != WORD))
		{
			ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
			return (-1);
		}
		if (stack->type == PIPE && (!stack->next || stack->next->type == PIPE))
		{
			ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
			return (-1);
		}
		stack = stack->next;
	}
	return (0);
}

void	execute_pipe(t_data *data)
{
	t_pipe_fd	fds;
	char		**failed_cmds;
	int			num_cmds;
	int			exit_codes[4096];
	int			i;

	fds.prev_fd = 0;
	num_cmds = count_segments(&data->stack, PIPE);
	if (num_cmds >= 1024 || num_cmds == -1)
		return ;
	failed_cmds = fork_for_pipe(data, num_cmds, fds);
	if (!failed_cmds || !*failed_cmds)
		return ;
	wait_for_children(num_cmds, exit_codes);
	i = -1;
	while (++i < num_cmds)
	{
		if (failed_cmds)
		{
			if (exit_codes[i] == 127)
				error_msg(failed_cmds[i]);
		}
	}
	free_array(failed_cmds);
}
