/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 19:33:43 by mabaghda          #+#    #+#             */
/*   Updated: 2025/09/13 19:57:45 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdio.h>

char	**fork_for_pipe(t_data *data, int num_cmds, t_pipe_fd fds)
{
	t_token	*tmp;
	char	**f_cmd;
	int		i;

	i = 0;
	tmp = data->stack;
	f_cmd = malloc(sizeof(char *) * (num_cmds + 1));
	if (!f_cmd)
		return (NULL);
	while (i < num_cmds)
	{
		if (tmp->type == PIPE)
		{
			if (!tmp->next)
            {
				//ft_putstr_fd
                printf("minishell: syntax error\n");
                for (int k = 0; k < i; k++)
                    free(f_cmd[k]);
                free(f_cmd);
                return (NULL);
            }
			tmp = tmp->next;
		}
		f_cmd[i] = ft_strdup(get_first_word(tmp));
		if (i < num_cmds - 1)
			pipe(fds.pfd);
		fds.last_cmd = (i == num_cmds - 1);
		if (fork_and_get_cmd(data, &fds, &tmp) == -1)
		{
			if (f_cmd)
				free_array(f_cmd);
			return (NULL);
		}
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
	if (!failed_cmds)
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
