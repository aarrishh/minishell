/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 17:13:10 by mabaghda          #+#    #+#             */
/*   Updated: 2025/08/21 11:25:46 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	has_operator(t_token *stack, t_token_type type)
{
	while (stack)
	{
		if (stack->type == type)
			return (1);
		stack = stack->next;
	}
	return (0);
}

char	*find_filename_out(t_token *stack, int i)
{
	int	count;

	count = 0;
	while (stack)
	{
		if ((stack->type == REDIR_OUT || stack->type == APPEND))
		{
			if (count == i)
			{
				if (stack->next)
					return (stack->next->string);
				else
					return (NULL);
			}
			count++;
		}
		stack = stack->next;
	}
	return (NULL);
}

void	redirect_cmd(t_data *data, char *cmd, int fd, int in_or_out)
{
	char	**main_cmd;
	char	*path;
	pid_t	pid;
	int		saved_stdout;

	main_cmd = ft_split(cmd, ' ');
	if (main_cmd[0] && is_builtin_cmd(main_cmd[0]))
	{
		saved_stdout = dup(in_or_out);
		if (dup2(fd, in_or_out) == -1)
		{
			// do we need error check?
			close(fd);
			return ;
		}
		built_in_functions(&data->stack, main_cmd[0], &data->env, data->split);
		free_array(main_cmd);
		dup2(saved_stdout, in_or_out);
		close(saved_stdout);
	}
	else
	{
		pid = fork();
		if (pid == 0)
		{
			if (dup2(fd, in_or_out) == -1)
			{
				// do we need error check?
				close(fd);
				return ;
			}
			path = split_path(&data->env, main_cmd[0]);
			if (!path)
				exit(127);
			if (execve(path, main_cmd, data->envp))
			{
				perror(main_cmd[0]);
				exit(126);
			}
			free_array(main_cmd);
			free(path);
		}
		else
		{
			g_exit_status = 127;
			wait(NULL);
		}
	}
}

int	find_and_open(t_data **data, int append, int i)
{
	int		fd;
	char	*filename;

	filename = find_filename_out((*data)->stack, i);
	if (!filename)
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		exit(1);
	}
	if (append)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("open");
		return (0);
	}
	return (fd);
}

void	redir_function(t_data *data, int append)
{
	int		fd;
	int		len;
	int		i;
	int		j;
	char	**split_redir;

	i = 0;
	j = 0;
	if (append)
		split_redir = split_operator(&data->stack, APPEND);
	else
		split_redir = split_operator(&data->stack, REDIR_OUT);
	len = two_dim_len(split_redir);
	while (i < len)
	{
		if (i != 0)
		{
			// if (fd)
			// 	close(fd);
			fd = find_and_open(&data, append, j);
			j++;
		}
		i++;
	}
	if (fd)
		redirect_cmd(data, split_redir[0], fd, 1);
	close(fd);
}
