/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 12:07:36 by mabaghda          #+#    #+#             */
/*   Updated: 2025/08/07 19:06:31 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

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
	i = 0;
	if (!commands)
		return (NULL);
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

void	execute_pipe(t_token **stack)
{
	char	**commands;
	char	**chgitem;
	pid_t	pid;
	int		i;
	int		cmd_len;
	int		new[2];
	int		old;

	old = -1;
	cmd_len = 0;
	i = 0;
	commands = split_pipe(stack);
	while (commands[cmd_len])
		cmd_len++;
	while (i < cmd_len)
	{
		if (i < cmd_len - 1 && pipe(new) == -1)
			return (perror("pipe"));
		chgitem = ft_split(commands[i], ' ');
		pipe(new);
		pid = fork();
		if (pid == 0)
			child(old, chgitem);
		else
			parent();
		i++;
	}
}

void	child(int *old, char **chgitem)
{
	int	i;

	i = 0;
	if (old != -1)
	{
		dup2(old, STDIN_FILENO);
		close(old);
	}
	if (chgitem[i + 1])
	{
		dup2(old[1], STDOUT_FILENO);
		execve("changeeeee", chgitem[0], chgitem);
	}
}

void	parent(void)
{
	;
}