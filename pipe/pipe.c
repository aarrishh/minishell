/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 19:33:43 by mabaghda          #+#    #+#             */
/*   Updated: 2025/08/09 19:36:06 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

void	child(int old, int *pfd, t_env **env, char **envp, char *cmd,
		int last_cmd)
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
	path = split_path(env, main_cmd[0]);
	execve(path, , envp);
	exit(0);
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

void	execute_pipe(t_token **stack, t_env **env, char **envp)
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
			child(old, pfd, env, envp, commands[i], i == num_cmds - 1);
		else
			parent(&old, pfd, i == num_cmds - 1);
		i++;
	}
	i = 0;
	while (i++ < num_cmds)
		wait(NULL);
	free_commands(commands);
}

// int has_pipe(t_token *stack)
// {
//  while (stack)
//  {
//   if (stack->type == PIPE)
//    return (1);
//   stack = stack->next;
//  }
//  return (0);
// }

void	execute_else(t_token **stack)
{
	pid_t	pid;
	char	**argv;

	argv = ft_split((*stack)->string, ' ');
	pid = fork();
	if (pid == 0)
	{
		if (!is_builtin(*stack))
			execve();
		perror("execvp");
		exit(1);
	}
	else
		wait(NULL);
}

int	is_builtin(t_token *stack)
{
	if (!stack || !stack->string)
		return (0);
	if (!ft_strcmp(stack->string, "echo"))
		return (1);
	if (!ft_strcmp(stack->string, "cd"))
		return (1);
	if (!ft_strcmp(stack->string, "pwd"))
		return (1);
	if (!ft_strcmp(stack->string, "export"))
		return (1);
	if (!ft_strcmp(stack->string, "unset"))
		return (1);
	if (!ft_strcmp(stack->string, "env"))
		return (1);
	if (!ft_strcmp(stack->string, "exit"))
		return (1);
	return (0);
}