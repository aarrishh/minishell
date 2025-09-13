/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 17:13:10 by mabaghda          #+#    #+#             */
/*   Updated: 2025/09/13 14:03:17 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_wait_status(void)
{
	int	status;

	waitpid(-1, &status, 0);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_exit_status = 128 + WTERMSIG(status);
	// g_exit_status = 127;
	// wait(NULL);
}

void	execute_command(t_data *data, t_command *cmd_struct)
{
	pid_t	pid;
	int		saved_in;
	int		saved_out;

	saved_in = -1;
	saved_out = -1;
	if (cmd_struct->execute == -1)
		return ;
	if (cmd_struct->cmd[0] && is_builtin_cmd(cmd_struct->cmd[0]))
	{
		builtin_redirs(cmd_struct, &saved_in, &saved_out);
		built_in_functions(data, &data->stack, cmd_struct->cmd[0]);
		restore_fd(&saved_in, &saved_out);
	}
	else
	{
		pid = fork();
		if (pid == 0)
			redirs_child(data, cmd_struct);
		else
			handle_wait_status();
	}
}

void	restore_fd(int *saved_in, int *saved_out)
{
	if (*saved_in != -1)
	{
		dup2(*saved_in, 0);
		close(*saved_in);
	}
	if (*saved_out != -1)
	{
		dup2(*saved_out, 1);
		close(*saved_out);
	}
}

void	redirs_child(t_data *data, t_command *cmd_struct)
{
	char	*path;
	char	**envp;

	dup_for_redirs(cmd_struct);
	path = split_path(&data->env, cmd_struct->cmd[0]);
	if (!path)
		exit(127);
	envp = env_to_envp(data->env);
	if (execve(path, cmd_struct->cmd, envp) == -1)
	{
		perror(cmd_struct->cmd[0]);
		exit(126);
	}
	free(path);
	exit(1);
}

void	builtin_redirs(t_command *cmd_struct, int *saved_in, int *saved_out)
{
	if (cmd_struct->input != 0)
	{
		*saved_in = dup(0);
		if (dup2(cmd_struct->input, 0) == -1)
		{
			close(cmd_struct->input);
			perror("dup2 input");
			return ;
		}
	}
	if (cmd_struct->output != 1)
	{
		*saved_out = dup(1);
		if (dup2(cmd_struct->output, 1) == -1)
		{
			close(cmd_struct->output);
			perror("dup2 output");
			return ;
		}
	}
}

void	dup_for_redirs(t_command *cmd_struct)
{
	if (cmd_struct->input != 0)
	{
		if (dup2(cmd_struct->input, 0) == -1)
		{
			// do we need error check?
			close(cmd_struct->input);
			return ;
		}
	}
	if (cmd_struct->output != 1)
	{
		if (dup2(cmd_struct->output, 1) == -1)
		{
			// do we need error check?
			close(cmd_struct->output);
			return ;
		}
	}
}
