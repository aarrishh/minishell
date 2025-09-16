/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimanuk <arimanuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 19:33:43 by mabaghda          #+#    #+#             */
/*   Updated: 2025/09/14 16:09:09 by arimanuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	validate_cmd(t_token **tmp, char **f_cmd, int i, int num_cmds)
{
	if (!*tmp)
		return (0);
	f_cmd[i] = ft_strdup(get_first_word(*tmp));
	if (!f_cmd[i])
		return (-1);
	if (i == num_cmds - 1)
		return (1);
	return (0);
}

void	loop_till_pipe(t_token **tmp)
{
	if (*tmp)
	{
		while ((*tmp) && (*tmp)->type != PIPE)
			(*tmp) = (*tmp)->next;
	}
}

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

void	wait_for_children(int num_cmds, int *exit_codes)
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

char	**fork_for_pipe(t_data *data, int num_cmds, t_pipe_fd fds)
{
	t_token	*tmp;
	char	**f_cmd;
	int		i;

	tmp = data->stack;
	f_cmd = malloc_help(num_cmds);
	if (!f_cmd)
		return (NULL);
	i = 0;
	while (i < num_cmds)
	{
		if (tmp->type == PIPE && tmp->next)
			tmp = tmp->next;
		if (validate_cmd(&tmp, f_cmd, i, num_cmds) == -1)
			return (free_array(f_cmd), NULL);
		if (i < num_cmds - 1)
			pipe(fds.pfd);
		fds.last_cmd = (i == num_cmds - 1);
		if (fork_and_get_cmd(data, &fds, &tmp) == -1)
			return (free_array(f_cmd), NULL);
		loop_till_pipe(&tmp);
		i++;
	}
	f_cmd[i] = NULL;
	return (f_cmd);
}
