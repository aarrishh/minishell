/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 17:13:10 by mabaghda          #+#    #+#             */
/*   Updated: 2025/08/14 12:36:19 by mabaghda         ###   ########.fr       */
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
	while (stack)
	{
		if ((stack->type == REDIR_OUT) || (stack->type == APPEND))
		{
			return (stack->next->string);
		}
		stack = stack->next;
	}
	return (NULL);
}

void	redir_function(t_data *data, int append)
{
	int		fd;
	char	*filename;

	// > : overwrite : O_WRONLY | O_CREAT | O_TRUNC
	// >> : append : O_WRONLY | O_CREAT | O_APPEND
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
		perror("dup2");
		close(fd);
		exit(1);
	}
	else
		redirect_in(data, fd, append);
	close(fd);
}

void	redirect_in(t_data *data, int fd, int append)
{
	;
}