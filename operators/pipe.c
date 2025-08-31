/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 19:33:43 by mabaghda          #+#    #+#             */
/*   Updated: 2025/08/31 19:53:44 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	child(t_data *data, t_pipe_fd *fds, char **cmd)
{
	char	*path;
	char	**envp;

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
	if (cmd[0] && is_builtin_cmd(cmd[0]))
	{
		built_in_functions(&data->stack, cmd[0], &data->env, data->split);
		free_array(cmd);
		exit(0);
	}
	else
	{
		envp = env_to_envp(data->env);
		path = split_path(&data->env, cmd[0]);
		if (!path)
			exit(127);
		execve(path, cmd, envp);
		free_array(cmd);
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

// char	**fork_for_pipe(t_data *data, char **commands, int num_cmds)
// {
// 	int			i;
// 	pid_t		pid;
// 	t_pipe_fd	fds;
// 	char		**main_cmd;
// 	char		**failed_cmds;

// 	i = 0;
// 	fds.prev_fd = 0;
// 	failed_cmds = malloc(sizeof(char *) * (num_cmds + 1));
// 	if (!failed_cmds)
// 		return (NULL);
// 	while (i < num_cmds)
// 	{
// 		if (i < num_cmds - 1)
// 			pipe(fds.pfd);
// 		fds.last_cmd = (i == num_cmds - 1);
// 		pid = fork();
// 		if (pid == 0)
// 			child(data, &fds, commands[i]);
// 		else
// 			parent(&fds);
// 		main_cmd = ft_split(commands[i], ' ');
// 		failed_cmds[i] = ft_strdup(main_cmd[0]);
// 		free_array(main_cmd);
// 		i++;
// 	}
// 	failed_cmds[i] = NULL;
// 	return (failed_cmds);
// }

// void	execute_pipe(t_data *data)
// {
// 	char	**commands;
// 	char	**failed_cmds;
// 	int		num_cmds;
// 	int		i;
// 	int		status;
// 	int		exit_codes[256];

// 	commands = split_operator(&data->stack, PIPE);
// 	num_cmds = two_dim_len(commands);
// 	i = 0;
// 	failed_cmds = fork_for_pipe(data, commands, num_cmds);
// 	if (!failed_cmds)
// 		return ;
// 	while (i < num_cmds)
// 	{
// 		waitpid(-1, &status, 0);
// 		if (WIFEXITED(status))
// 		{
// 			g_exit_status = WEXITSTATUS(status);
// 			exit_codes[i] = g_exit_status;
// 		}
// 		else if (WIFSIGNALED(status))
// 		{
// 			g_exit_status = 128 + WTERMSIG(status);
// 			exit_codes[i] = g_exit_status;
// 		}
// 		i++;
// 	}
// 	i = num_cmds - 1;
// 	while (i >= 0)
// 	{
// 		if (exit_codes[i] == 127)
// 			printf("%s: command not found\n", failed_cmds[i]);
// 		i--;
// 	}
// 	free_array(commands);
// 	free_array(failed_cmds);
// }

char	**make_arr_command(t_token *stack, t_token_type type)
{
	t_token	*tmp;
	char	**cmd;
	int		len;
	int		i;

	len = 0;
	i = 0;
	tmp = stack;
	while (tmp && tmp->type != type)
	{
		len++;
		tmp = tmp->next;
	}
	cmd = (char **)malloc(sizeof(char *) * (len + 1));
	tmp = stack;
	while (i < len && tmp && tmp->type != type)
	{
		cmd[i] = ft_strdup(tmp->string);
		if (!cmd[i])
			free_array(cmd);
		tmp = tmp->next;
		i++;
	}
	cmd[i] = NULL;
	return (cmd);
}

char	**fork_for_pipe(t_data *data, int num_cmds)
{
	int			i;
	pid_t		pid;
	t_pipe_fd	fds;
	t_token		*tmp;
	char		**commands;
	char		**failed_cmds;

	i = 0;
	fds.prev_fd = 0;
	tmp = data->stack;
	failed_cmds = malloc(sizeof(char *) * (num_cmds + 1));
	if (!failed_cmds)
		return (NULL);
	while (i < num_cmds && tmp)
	{
		if (ft_strcmp(tmp->string, "|") == 0)
		{
			tmp = tmp->next;
			i++;
			continue ;
		}
		commands = make_arr_command(tmp, PIPE);
		while (tmp && tmp->type != PIPE)
			tmp = tmp->next;
		if (tmp && tmp->type == PIPE)
			tmp = tmp->next;
		if (i < num_cmds - 1)
			pipe(fds.pfd);
		fds.last_cmd = (i == num_cmds - 1);
		pid = fork();
		if (pid == 0)
			child(data, &fds, commands);
		else
			parent(&fds);
		failed_cmds[i] = ft_strdup(commands[0]);
		i++;
	}
	failed_cmds[i] = NULL;
	return (failed_cmds);
}

int	count_segments(t_token **stack, t_token_type type)
{
	int		len;
	t_token	*tmp;

	tmp = *stack;
	len = 0;
	while (tmp)
	{
		if (tmp->type == type)
			len++;
		tmp = tmp->next;
	}
	return (len + 1);
}

void	execute_pipe(t_data *data)
{
	char **failed_cmds;
	int num_cmds;
	int i;
	int status;
	int exit_codes[256];

	num_cmds = count_segments(&data->stack, PIPE);
	i = 0;
	failed_cmds = fork_for_pipe(data, num_cmds);
	if (!failed_cmds)
		return ;
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
	i = num_cmds - 1;
	while (i >= 0)
	{
		if (exit_codes[i] == 127)
			printf("%s: command not found\n", failed_cmds[i]);
		i--;
	}
	free_array(failed_cmds);
}
