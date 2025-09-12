/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 19:49:51 by mabaghda          #+#    #+#             */
/*   Updated: 2025/09/12 23:51:28 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	child_fd_setup(t_pipe_fd *fds)
{
	if (fds->prev_fd != 0)
	{
		dup2(fds->prev_fd, 0);
		close(fds->prev_fd);
	}
	if (!fds->last_cmd)
	{
		close(fds->pfd[0]);
		dup2(fds->pfd[1], 1);
		close(fds->pfd[1]);
	}
}

void	child(t_data *data, t_pipe_fd *fds, t_token *tmp, char **cmd)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	child_fd_setup(fds);
	// printf(tmp[0]-> %s\n", (tmp)->string);
	// printf("cmd[0]-> %s\n", cmd[0]);
	// printf("cmd[1]-> %s\n", cmd[2]);
	// printf("cmd[2]-> %s\n", cmd[3]);
	if (tmp && (has_operator(tmp, REDIR_IN) || has_operator(tmp, REDIR_OUT)
			|| has_operator(tmp, APPEND) || has_operator(tmp, HEREDOC)))
	{
		if (operators(data, tmp) == -1)
			exit(0);
		exit(0);
	}
	else if (cmd[0] && is_builtin_cmd((tmp)->string))
	{
		built_in_functions(data, (tmp)->string);
		exit(0);
	}
	else
		exec_external_command(data, cmd);
}

void	parent(t_pipe_fd *fds)
{
	if (fds->prev_fd != 0)
		close(fds->prev_fd);
	if (!fds->last_cmd)
	{
		close(fds->pfd[1]);
		fds->prev_fd = fds->pfd[0];
	}
}

void	fork_and_get_cmd(t_data *data, t_pipe_fd *fds, t_token **stack)
{
	pid_t	pid;
	t_token	*tmp;
	char	**command;

	tmp = *stack;
	command = NULL;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type != WORD && tmp->next)
			tmp = tmp->next;
		else
			command = add_arg_to_cmd(command, tmp->string);
		tmp = tmp->next;
	}
	pid = fork();
	if (pid == -1)
		return (perror("fork"));
	if (pid == 0)
		child(data, fds, *stack, command);
	else
		parent(fds);
	while ((*stack) && (*stack)->type != PIPE)
		(*stack) = (*stack)->next;
}
