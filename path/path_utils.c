/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arina <arina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 18:23:55 by mabaghda          #+#    #+#             */
/*   Updated: 2025/09/14 10:17:56 by arina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execve_case(char *cmd, char **path, char **envp)
{
	perror(cmd);
	free(*path);
	free_array(envp);
	exit(127);
}

int	is_directory(const char *path)
{
	struct stat	st;

	if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
		return (1);
	return (0);
}

void	dir_error(char **path, char **envp, char **cmd)
{
	ft_putstr_fd(cmd[0], 2);
	ft_putstr_fd(": Is a directory\n", 2);
	free(*path);
	free_array(envp);
	exit(126);
}
