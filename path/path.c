/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arina <arina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 15:50:18 by mabaghda          #+#    #+#             */
/*   Updated: 2025/09/14 10:20:15 by arina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*find_path(t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "PATH") == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

static char	*try_paths(char **splitted_path, char *cmd)
{
	int		i;
	char	*joined;
	char	*full;

	i = 0;
	while (splitted_path[i])
	{
		joined = ft_strjoin(splitted_path[i], "/");
		full = ft_strjoin(joined, cmd);
		free(joined);
		if (access(full, X_OK) == 0)
		{
			free_array(splitted_path);
			return (full);
		}
		free(full);
		i++;
	}
	free_array(splitted_path);
	return (NULL);
}

char	*split_path(t_env **env, char *cmd)
{
	t_env	*path;
	char	**splitted_path;

	path = find_path(env);
	if (!path)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (cmd);
	}
	splitted_path = ft_split(path->value, ':');
	return (try_paths(splitted_path, cmd));
}

void	child_process_execution(t_env **env, char **cmd)
{
	char	*path;
	char	**envp;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	change_shlvl_value(env, cmd);
	if (!cmd[0])
	{
		error_msg("minishell");
		exit(127);
	}
	envp = env_to_envp(*env);
	if (!envp)
		exit(1);
	path = split_path(env, cmd[0]);
	if (!path)
	{
		free_array(envp);
		exit(127);
	}
	if (is_directory(path))
		dir_error(&path, envp, cmd);
	if (execve(path, cmd, envp) == -1)
		execve_case(cmd[0], &path, envp);
}

int	in_set(char *s, char c)
{
	while (*s)
	{
		if (*s == c)
			return (1);
		s++;
	}
	return (0);
}

// void	parent_process_handling(pid_t pid, int *status, char **cmd)
// {
// 	int	sig;

// 	signal(SIGINT, SIG_IGN);
// 	signal(SIGQUIT, SIG_IGN);
// 	if (waitpid(pid, status, 0) == -1)
// 		perror("waitpid");
// 	signal(SIGINT, sigint_handler);
// 	signal(SIGQUIT, sigquit_handler);
// 	if (WIFEXITED(*status))
// 		g_exit_status = WEXITSTATUS(*status);
// 	else if (WIFSIGNALED(*status))
// 	{
// 		sig = WTERMSIG(*status);
// 		g_exit_status = 128 + sig;
// 		if (sig == SIGINT)
// 			write(1, "\n", 1);
// 		else if (sig == SIGQUIT)
// 			write(1, "Quit: 3\n", 8);
// 	}
// 	if (g_exit_status == 127)
// 	{
// 		if (in_set(cmd[0], '/'))
// 			error_msg_dir(cmd[0]);
// 		else
// 			error_msg(cmd[0]);
// 	}
// }
