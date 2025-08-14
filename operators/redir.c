/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 17:13:10 by mabaghda          #+#    #+#             */
/*   Updated: 2025/08/14 15:10:51 by mabaghda         ###   ########.fr       */
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

void	redir_function(t_data *data, int append)
{
	int		fd;
	char	*filename;

	filename = find_filename(data->stack);
	if (append)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("open");
		exit(1);
	}
	if (dup2(fd, 1) == -1)
	{
		// perror("dup2");
		close(fd);
		exit(1);
	}
	else
		redirect_in(data, append);
	close(fd);
}

int	redir_file(t_token **stack, t_token_type type)
{
	t_token	*tmp;

	tmp = *stack;
	while (tmp)
	{
		if ((tmp->type == type) || tmp->next != NULL)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

// char	*split_till_op(t_token **stack, t_token_type type)
// {
// 	t_token	*tmp;
// 	int		i;
// 	char	**commands;
// 	char	*to_free;
// 	char	*joined;

// 	tmp = *stack;
// 	commands = malloc(sizeof(char *) * (len_by_pipe(stack) + 2));
// 	if (!commands)
// 		return (NULL);
// 	i = 0;
// 	commands[i] = ft_strdup("");
// 	while (tmp)
// 	{
// 		if (tmp->type == PIPE)
// 		{
// 			i++;
// 			commands[i] = ft_strdup("");
// 		}
// 		else
// 		{
// 			to_free = commands[i];
// 			joined = ft_strjoin(tmp->string, " ");
// 			commands[i] = ft_strjoin(commands[i], joined);
// 			free(to_free);
// 			free(joined);
// 		}
// 		tmp = tmp->next;
// 	}
// 	commands[i + 1] = NULL;
// 	return (commands);
// }

void	redirect_in(t_data *data, int append)
{
	char **split_op;
	char **main_cmd;
	char *path;

	if (append)
	{
		split_op = split_operator(&data->stack, APPEND);
		if (!split_op)
			return ;
		if (!redir_file(&data->stack, APPEND))
		{
			printf("minishell: syntax error near unexpected token `newline'\n");
			return ;
		}
	}
	else
	{
		split_op = split_operator(&data->stack, REDIR_OUT);
		if (!split_op)
			return ;
		if (!redir_file(&data->stack, REDIR_OUT))
		{
			printf("minishell: syntax error near unexpected token `newline'\n");
			return ;
		}
	}

	main_cmd = ft_split(split_op[0], ' ');
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