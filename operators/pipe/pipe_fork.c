/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 19:49:51 by mabaghda          #+#    #+#             */
/*   Updated: 2025/09/13 19:32:51 by mabaghda         ###   ########.fr       */
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

// int	check_pipe(t_token **stack)
// {
// 	t_token	*tmp;

// 	tmp = *stack;
// 	while (tmp)
// 	{
// 		if (tmp->type != WORD && tmp->next->type == PIPE)
// 		{
// 			ft_putstr_fd("minishell", 2);
// 			ft_putstr_fd(": syntax error near unexpected token `|'\n", 2);
// 			return (-1);
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (0);
// }

void	child(t_data *data, t_pipe_fd *fds, t_token *tmp, char **cmd)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	child_fd_setup(fds);
	if (tmp && (has_operator(tmp, REDIR_IN) || has_operator(tmp, REDIR_OUT)
			|| has_operator(tmp, APPEND) || has_operator(tmp, HEREDOC)))
	{
		if (operators(data, tmp) == -1)
			exit(1);
		exit(0);
	}
	else if (cmd[0] && is_builtin_cmd(tmp->string))
	{
		built_in_functions(data, &tmp, tmp->string);
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

int	fork_and_get_cmd(t_data *data, t_pipe_fd *fds, t_token **stack)
{
	pid_t	pid;
	t_token	*tmp;
	t_token	*start;
	char	**command;

	tmp = *stack;
	start = *stack;
	command = NULL;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type != WORD && tmp->next->type == PIPE)
		{
			ft_putstr_fd("minishell", 2);
			ft_putstr_fd(": syntax error near unexpected token `|'\n", 2);
			return (-1);
		}
		if (tmp->type != WORD && tmp->next)
			tmp = tmp->next;
		else
			command = add_arg_to_cmd(command, tmp->string);
		tmp = tmp->next;
	}
	pid = fork();
	if (pid == -1)
		return (perror("fork"), free_array(command), -1);
	else if (pid == 0)
		child(data, fds, start, command);
	else
		parent(fds);
	free_array(command);
	return (0);
}
