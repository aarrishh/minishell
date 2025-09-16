/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 20:00:48 by mabaghda          #+#    #+#             */
/*   Updated: 2025/09/16 18:48:13 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*create_file(int i, int *fd)
{
	int		fd_0;
	char	*num;
	char	*filename;

	fd_0 = 0;
	filename = NULL;
	num = ft_itoa(i);
	filename = ft_strjoin("/tmp/arish_manan_heredoc_", num);
	free(num);
	fd_0 = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd && *fd)
		*fd = fd_0;
	return (filename);
}

int	find_and_open(char *filename, t_token_type type)
{
	char	*error;
	int		fd;

	if (type == APPEND)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		error = ft_strjoin("minishell: ", filename);
		perror(error);
		free(error);
		return (-1);
	}
	return (fd);
}

void	handle_wait_status(void)
{
	int	status;

	waitpid(-1, &status, 0);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_exit_status = 128 + WTERMSIG(status);
}

void	wait_sig_hd(pid_t pid, int *status)
{
	signal(SIGINT, SIG_IGN);
	waitpid(pid, status, 0);
	signal(SIGINT, SIG_DFL);
}
