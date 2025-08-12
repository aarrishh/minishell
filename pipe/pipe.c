/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimanuk <arimanuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 19:33:43 by mabaghda          #+#    #+#             */
/*   Updated: 2025/08/11 18:08:02 by arimanuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	len_by_pipe(t_token **stack)
{
	t_token	*tmp;
	int		len;

	len = 0;
	tmp = *stack;
	while (tmp)
	{
		if (tmp->type == PIPE)
			len++;
		tmp = tmp->next;
	}
	return (len);
}

char	**split_pipe(t_token **stack)
{
	t_token	*tmp;
	int		len;
	int		i;
	char	**commands;
	char	*old;
	char	*joined;

	tmp = *stack;
	len = len_by_pipe(stack);
	commands = malloc(sizeof(char *) * (len + 2));
	if (!commands)
		return (NULL);
	i = 0;
	commands[i] = ft_strdup("");
	while (tmp)
	{
		if (tmp->type == PIPE)
		{
			i++;
			commands[i] = ft_strdup("");
		}
		else
		{
			old = commands[i];
			joined = ft_strjoin(tmp->string, " ");
			commands[i] = ft_strjoin(commands[i], joined);
			free(old);
			free(joined);
		}
		tmp = tmp->next;
	}
	commands[i + 1] = NULL;
	return (commands);
}

void	child(t_token **stack, int old, int *pfd, t_env **env, char **envp,
		char *cmd, int last_cmd, char **split)
{
	char	**main_cmd;
	char	*path;

	if (old != 0)
	{
		dup2(old, 0);
		close(old);
	}
	if (!last_cmd)
	{
		close(pfd[0]);
		dup2(pfd[1], 1);
		close(pfd[1]);
	}
	main_cmd = ft_split(cmd, ' ');
	if (main_cmd[0] && is_builtin_cmd(main_cmd[0]))
	{
		built_in_functions(stack, main_cmd[0], env, split);
		free_array(main_cmd);
		exit(0);
	}
	else
	{
		path = split_path(env, main_cmd[0]);
		execve(path, main_cmd, envp);
		free_array(main_cmd);
		free(path);
		exit(1);
	}
}

void	parent(int *old, int *pfd, int last_cmd)
{
	if (*old != 0)
		close(*old);
	if (!last_cmd)
	{
		close(pfd[1]);
		*old = pfd[0];
	}
}

void	execute_pipe(t_token **stack, t_env **env, char **envp, char **split)
{
	char	**commands;
	int		num_cmds;
	int		i;
	int		pfd[2];
	pid_t	pid;
	int		old;

	commands = split_pipe(stack);
	num_cmds = 0;
	while (commands[num_cmds])
		num_cmds++;
	i = 0;
	old = 0;
	while (i < num_cmds)
	{
		if (i < num_cmds - 1)
			pipe(pfd);
		pid = fork();
		if (pid == 0)
			child(stack, old, pfd, env, envp, commands[i], i == num_cmds - 1, split);
		else
			parent(&old, pfd, i == num_cmds - 1);
		i++;
	}
	i = 0;
	while (i++ < num_cmds)
		wait(NULL);
	free_array(commands);
}

int	has_pipe(t_token *stack)
{
	while (stack)
	{
		if (stack->type == PIPE)
			return (1);
		stack = stack->next;
	}
	return (0);
}
void	execute_else(t_env **env, char **cmd, char **envp)
{
	pid_t	pid;
	char	*path;

	pid = fork();
	if (pid == 0)
	{
		path = split_path(env, cmd[0]);
		if (!path)
			return ;
		execve(path, cmd, envp);
		{
			// perror(cmd[0]);
			exit(1);
		}
		
	}
	else
		wait(NULL);
}

void	*free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
}

int	is_builtin_cmd(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	if (!ft_strcmp(cmd, "cd"))
		return (1);
	if (!ft_strcmp(cmd, "pwd"))
		return (1);
	if (!ft_strcmp(cmd, "export"))
		return (1);
	if (!ft_strcmp(cmd, "unset"))
		return (1);
	if (!ft_strcmp(cmd, "env"))
		return (1);
	if (!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}
