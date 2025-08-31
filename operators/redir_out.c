/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 17:13:10 by mabaghda          #+#    #+#             */
/*   Updated: 2025/08/28 21:12:54 by mabaghda         ###   ########.fr       */
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

void	redirect_cmd(t_data *data, char *cmd, int fd, int in_or_out)
{
	char	**main_cmd;
	char	*path;
	pid_t	pid;
	int		status;
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
			waitpid(-1, &status, 0);
			if (WIFEXITED(status))
				g_exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				g_exit_status = 128 + WTERMSIG(status);
			// g_exit_status = 127;
			// wait(NULL);
		}
	}
}

int	find_and_open(char *filename, int append)
{
	int	fd;

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

void	redir_function(t_data *data)
{
	t_token	*tmp;
	char	*cmd;
	int		fd;

	tmp = data->stack;
	cmd = data->stack->string;
	while (tmp)
	{
		if (tmp->type == APPEND && tmp->next)
		{
			fd = find_and_open(tmp->next->string, 1);
		}
		else if (tmp->type == REDIR_OUT && tmp->next)
		{
			fd = find_and_open(tmp->next->string, 0);
		}
		if (tmp->next == NULL && (tmp->type == APPEND
				|| tmp->type == REDIR_OUT))
		{
			printf("minishell: syntax error near unexpected token `newline'\n");
			g_exit_status = 2;
			return ;
		}
		if (tmp->type == WORD && tmp->next == NULL)
			redirect_cmd(data, cmd, fd, 1);
		tmp = tmp->next;
	}
}

// char	*find_filename(t_token *stack, int i)
// {
// 	int	count;

// 	count = 0;
// 	while (stack)
// 	{
// 		if ((stack->type == REDIR_OUT || stack->type == APPEND))
// 		{
// 			if (count == i)
// 			{
// 				if (stack->next)
// 					return (stack->next->string);
// 				else
// 					return (NULL);
// 			}
// 			count++;
// 		}
// 		stack = stack->next;
// 	}
// 	return (NULL);
// }

// void	start_redirs(char **split_redir, t_data *data, int append)
// {
// 	int	fd;
// 	int	len;
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	fd = 0;
// 	len = two_dim_len(split_redir);
// 	while (i < len)
// 	{
// 		if (i != 0)
// 		{
// 			if (fd)
// 				close(fd);
// 			fd = find_and_open(&data, append, j);
// 			j++;
// 		}
// 		i++;
// 	}
// 	if (fd)
// 		redirect_cmd(data, split_redir[0], fd, append);
// 	close(fd);
// }

// void	redir_function(t_data *data)
// {
// 	char	**split_redir;
// 	char	**inner_split;
// 	int		i;

// 	i = 0;
// 	if (has_operator(data->stack, APPEND))
// 	{
// 		split_redir = split_operator(&data->stack, APPEND);
// 		if (!split_redir)
// 			return ;
// 		start_redirs(split_redir, data, 1);
// 		if (has_operator(data->stack, REDIR_OUT))
// 		{
// 			while (split_redir[i])
// 			{
// 				inner_split = ft_split(split_redir[i], '>');
// 				i++;
// 			}
// 			start_redirs(inner_split, data, 0);
// 		}
// 	}
// 	else if (has_operator(data->stack, REDIR_OUT))
// 	{
// 		split_redir = split_operator(&data->stack, REDIR_OUT);
// 		if (!split_redir)
// 			return ;
// 		start_redirs(split_redir, data, 1);
// 		if (has_operator(data->stack, APPEND))
// 		{
// 			while (split_redir[i])
// 			{
// 				inner_split = ft_split(split_redir[i], '>>');
// 				i++;
// 			}
// 			start_redirs(inner_split, data, 0);
// 		}
// 	}
// }
