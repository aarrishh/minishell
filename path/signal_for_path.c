/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_for_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arina <arina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 10:20:42 by arina             #+#    #+#             */
/*   Updated: 2025/09/14 10:22:55 by arina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	handle_signal_status(int *status)
{
	int	sig;

	if (WIFEXITED(*status))
		g_exit_status = WEXITSTATUS(*status);
	else if (WIFSIGNALED(*status))
	{
		sig = WTERMSIG(*status);
		g_exit_status = 128 + sig;
		if (sig == SIGINT)
			write(1, "\n", 1);
		else if (sig == SIGQUIT)
			write(1, "Quit: 3\n", 8);
	}
}

static void	handle_cmd_error(char **cmd)
{
	if (g_exit_status == 127)
	{
		if (in_set(cmd[0], '/'))
			error_msg_dir(cmd[0]);
		else
			error_msg(cmd[0]);
	}
}

void	parent_process_handling(pid_t pid, int *status, char **cmd)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (waitpid(pid, status, 0) == -1)
		perror("waitpid");
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	handle_signal_status(status);
	handle_cmd_error(cmd);
}
