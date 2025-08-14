/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 17:13:10 by mabaghda          #+#    #+#             */
/*   Updated: 2025/08/14 18:06:45 by mabaghda         ###   ########.fr       */
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

char	*find_filename(t_token *stack)
{
	char	*filename;

	filename = NULL;
	while (stack)
	{
		if ((stack->type == REDIR_OUT) || (stack->type == APPEND))
		{
			return (stack->next->string);
		}
		stack = stack->next;
	}
	return (filename);
}

int	redir_file(t_token **stack, t_token_type type)
{
	t_token	*tmp;

	tmp = *stack;
	while (tmp)
	{
		if ((tmp->type == type) && (tmp->next != NULL))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	redirect_in(t_data *data, char *cmd, int append)
{
	char	**main_cmd;
	char	*path;

	if (append)
	{
		if (!redir_file(&data->stack, APPEND))
		{
			printf("minishell: syntax error near unexpected token `newline'\n");
			return ;
		}
	}
	else
	{
		if (!redir_file(&data->stack, REDIR_OUT))
		{
			printf("minishell: syntax error near unexpected token `newline'\n");
			return ;
		}
	}
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

int	find_and_open(t_data **data, char **filename, int append)
{
	int	fd;

	*filename = find_filename((*data)->stack);
	if (append)
		fd = open(*filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(*filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
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
	int		saved_stdout;
	char	**split_redir;

	i = 0;
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
			fd = find_and_open(&data, &split_redir[i], append);
			if (dup2(fd, 1) == -1)
			{
				// do we need error check?
				close(fd);
				exit(1);
			}
		}
		i++;
	}
	redirect_in(data, split_redir[0], append);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
	close(fd);
}
