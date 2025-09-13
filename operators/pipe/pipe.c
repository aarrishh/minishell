/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 19:33:43 by mabaghda          #+#    #+#             */
/*   Updated: 2025/09/14 02:43:59 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdio.h>

static char	**malloc_help(int len)
{
	char	**f_cmd;
	int		i;

	i = 0;
	f_cmd = (char **)malloc(sizeof(char *) * (len + 1));
	if (!f_cmd)
		return (NULL);
	while (i < len)
		f_cmd[i++] = NULL;
	return (f_cmd);
}

static int	validate_cmd(t_token **tmp, char **f_cmd, int i,
		int num_cmds)
{
	if (!*tmp)
		return (0);
	if ((*tmp)->type == WORD && (*tmp)->next && (*tmp)->next->type == PIPE
		&& (*tmp)->next->next && (*tmp)->next->next->type == PIPE)
		return (-1);
	if ((*tmp)->type == PIPE)
	{
		if (!(*tmp)->next || (*tmp)->next->type == PIPE)
			return (ft_putstr_fd("minishell: syntax error\n", 2), free_array(f_cmd), -1);
		*tmp = (*tmp)->next;
	}
	f_cmd[i] = ft_strdup(get_first_word(*tmp));
	if (!f_cmd[i])
		return (-1);
	if (i == num_cmds - 1)
		return (1);
	return (0);
}

char	**fork_for_pipe(t_data *data, int num_cmds, t_pipe_fd fds)
{
	t_token	*tmp;
	char	**f_cmd;
	int		i;
	int		check;

	tmp = data->stack;
	f_cmd = malloc_help(num_cmds);
	if (!f_cmd)
		return (NULL);
	i = 0;
	while (i < num_cmds)
	{
		check = validate_cmd(&tmp, f_cmd, i, num_cmds);
		if (check == -1)
			return (free_array(f_cmd), NULL);
		if (pipe(fds.pfd) == -1)
			return (perror("pipe"), free_array(f_cmd), NULL);
		fds.last_cmd = (i == num_cmds - 1);
		if (fork_and_get_cmd(data, &fds, &tmp) == -1)
			return (free_array(f_cmd), NULL);
		while (tmp && tmp->type != PIPE)
			tmp = tmp->next;
		i++;
	}
	f_cmd[i] = NULL;
	return (f_cmd);
}

static void	wait_for_children(int num_cmds, int *exit_codes)
{
	int	i;
	int	status;

	i = 0;
	while (i < num_cmds)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
		{
			g_exit_status = WEXITSTATUS(status);
			exit_codes[i] = g_exit_status;
		}
		else if (WIFSIGNALED(status))
		{
			g_exit_status = 128 + WTERMSIG(status);
			exit_codes[i] = g_exit_status;
		}
		i++;
	}
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
	failed_cmds = fork_for_pipe(data, num_cmds, fds);
	if (!failed_cmds || !*failed_cmds)
		return ;
	wait_for_children(num_cmds, exit_codes);
	i = 0;
	while (i < num_cmds)
	{
		if (failed_cmds)
		{
			if (exit_codes[i] == 127)
				error_msg(failed_cmds[i]);
		}
		i++;
	}
	free_array(failed_cmds);
}
