/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 19:49:51 by mabaghda          #+#    #+#             */
/*   Updated: 2025/09/11 21:01:16 by mabaghda         ###   ########.fr       */
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
	if (tmp && (has_operator(tmp, REDIR_IN) || has_operator(tmp, REDIR_OUT)
			|| has_operator(tmp, APPEND) || has_operator(tmp, HEREDOC)))
	{
		operators(data, tmp);
		exit(0);
	}
	else if (cmd[0] && is_builtin_cmd(cmd[0]))
	{
		built_in_functions(data, cmd[0]);
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

void	fork_and_get_cmd(t_data *data, t_pipe_fd *fds, t_token **tmp)
{
	pid_t	pid;
	t_token	*start;
	char	**commands;

	start = *tmp;
	commands = make_command_pipe(*tmp);
	while (*tmp && (*tmp)->type != PIPE)
		*tmp = (*tmp)->next;
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free_array(commands);
		return ;
	}
	if (pid == 0)
		child(data, fds, start, commands);
	else
		parent(fds);
	free_array(commands);
}
