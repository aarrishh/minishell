/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arina <arina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:23:27 by arimanuk          #+#    #+#             */
/*   Updated: 2025/09/14 10:13:38 by arina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	sigint_handler(int sig)
{
	(void)sig;
	g_exit_status = 130;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	handle_ctrl_d(void)
{
	write(1, "exit\n", 5);
	rl_clear_history();
	g_exit_status = 0;
	exit(g_exit_status);
}

void	sigquit_handler(int sig)
{
	(void)sig;
}

void	setup_signals(void)
{
	rl_clear_history();
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
}
