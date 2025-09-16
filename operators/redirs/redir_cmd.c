/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 11:26:23 by mabaghda          #+#    #+#             */
/*   Updated: 2025/09/16 13:11:22 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	handle_redir_in(t_command *cmd_s, t_token **tmp)
{
	if (cmd_s->input != 0)
		close(cmd_s->input);
	cmd_s->input = open_rdirin((*tmp)->next->string);
	if (cmd_s->input == -1)
	{
		cmd_s->execute = -1;
		g_exit_status = 1;
		return (-1);
	}
	*tmp = (*tmp)->next;
	return (0);
}

int	handle_redir_out(t_command *cmd_s, t_token **tmp)
{
	cmd_s->output = find_and_open((*tmp)->next->string, (*tmp)->type);
	if (cmd_s->output == -1)
	{
		cmd_s->execute = -1;
		g_exit_status = 1;
		return (-1);
	}
	*tmp = (*tmp)->next;
	return (0);
}

static int	handle_token(t_data *data, t_token **tmp, t_command *cmd_s, int *i)
{
	if ((*tmp)->type == WORD)
		cmd_s->cmd = add_cmd(cmd_s, *tmp);
	else if ((*tmp)->type == REDIR_IN && (*tmp)->next
		&& (*tmp)->next->type == WORD)
		return (handle_redir_in(cmd_s, tmp));
	else if (((*tmp)->type == REDIR_OUT || (*tmp)->type == APPEND)
		&& (*tmp)->next && (*tmp)->next->type == WORD)
		return (handle_redir_out(cmd_s, tmp));
	else if ((*tmp)->type == HEREDOC && (*tmp)->next
		&& (*tmp)->next->type == WORD)
		handle_heredoc(data, cmd_s, tmp, (*i)++);
	else
	{
		error_nl_or_type(cmd_s, (*tmp)->next);
		return (-1);
	}
	return (0);
}

void	loop_over_execute(t_data *data, t_token *stack, t_command *cmd_s)
{
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = stack;
	while (tmp && tmp->type != PIPE)
	{
		if (handle_token(data, &tmp, cmd_s, &i) == -1)
			return ;
		tmp = tmp->next;
	}
}

int	operators(t_data *data, t_token *stack)
{
	t_command	cmd_struct;

	init_cmd(&cmd_struct);
	loop_over_execute(data, stack, &cmd_struct);
	if (cmd_struct.execute == -1)
	{
		if (cmd_struct.input != 0)
			close(cmd_struct.input);
		if (cmd_struct.output != 1)
			close(cmd_struct.output);
		if (cmd_struct.cmd)
			free_array(cmd_struct.cmd);
		return (-1);
	}
	execute_command(data, &cmd_struct);
	mer_verjin_huys(&cmd_struct);
	if (cmd_struct.input != 0)
		close(cmd_struct.input);
	if (cmd_struct.output != 1)
		close(cmd_struct.output);
	if (cmd_struct.cmd)
		free_array(cmd_struct.cmd);
	return (0);
}
