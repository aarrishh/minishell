/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimanuk <arimanuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 19:33:43 by mabaghda          #+#    #+#             */
/*   Updated: 2025/08/14 15:29:47 by arimanuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	child(t_data *data, t_pipe_fd *fds, char *cmd)
{
	char	**main_cmd;
	char	*path;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
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
	main_cmd = ft_split(cmd, ' ');
	if (main_cmd[0] && is_builtin_cmd(main_cmd[0]))
	{
		built_in_functions(&data->stack, main_cmd[0], &data->env, data->split);
		free_array(main_cmd);
		exit(0);
	}
	else
	{
		path = split_path(&data->env, main_cmd[0]);
		execve(path, main_cmd, data->envp);
		free_array(main_cmd);
		free(path);
		exit(1);
	}
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

int	two_dim_len(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	execute_pipe(t_data *data)
{
	char		**commands;
	int			num_cmds;
	int			i;
	pid_t		pid;
	t_pipe_fd	fds;

	commands = split_pipe(&data->stack);
	num_cmds = two_dim_len(commands);
	i = 0;
	while (i < num_cmds)
	{
		if (i < num_cmds - 1)
			pipe(fds.pfd);
		fds.last_cmd = (i == num_cmds - 1);
		pid = fork();
		if (pid == 0)
			child(data, &fds, commands[i]);
		else
			parent(&fds);
		i++;
	}
	i = 0;
	while (i++ < num_cmds)
		wait(NULL);
	free_array(commands);
}

int	has_pipe(t_token *stack)
{
	while (stack)
	{
		if (stack->type == PIPE)
			return (1);
		stack = stack->next;
	}
	return (0);
}
