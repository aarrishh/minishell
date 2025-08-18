/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 17:13:10 by mabaghda          #+#    #+#             */
/*   Updated: 2025/08/18 12:57:43 by mabaghda         ###   ########.fr       */
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

void	redirect_cmd(t_data *data, char *cmd)
{
	char	**main_cmd;
	char	*path;

	main_cmd = ft_split(cmd, ' ');
	if (main_cmd[0] && is_builtin_cmd(main_cmd[0]))
	{
		built_in_functions(&data->stack, main_cmd[0], &data->env, data->split);
		free_array(main_cmd);
	}
	else
	{
		path = split_path(&data->env, main_cmd[0]);
		if (!path)
			return ;
		execve(path, main_cmd, data->envp);
		free_array(main_cmd);
		free(path);
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
		exit(1);
	}
	return (fd);
}

void	redir_function(t_data *data, int append)
{
	int		fd;
	int		len;
	int		i;
	int		j;
	int		saved_stdout;
	char	**split_redir;

	i = 0;
	j = 0;
	saved_stdout = dup(STDOUT_FILENO);
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
	if (dup2(fd, 1) == -1)
	{
		// do we need error check?
		close(fd);
		exit(1);
	}
	redirect_cmd(data, split_redir[0]);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
	close(fd);
}
