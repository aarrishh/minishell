/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 11:26:23 by mabaghda          #+#    #+#             */
/*   Updated: 2025/08/20 18:27:34 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_filename_in(t_token *stack, int i)
{
	int	count;

	count = 0;
	while (stack)
	{
		if (stack->type == REDIR_IN)
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

int	open_rdirin(t_token *stack, int i)
{
	char	*filename;
	int		fd;

	filename = find_filename_in(stack, i);
	if (!filename)
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		exit(1);
	}
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return (0);
	}
	return (fd);
}

void	redir_in(t_data *data)
{
	int		fd;
	int		len;
	int		i;
	int		j;
	char	**split_rdrin;

	i = 0;
	j = 0;
	split_rdrin = split_operator(&data->stack, REDIR_IN);
	len = two_dim_len(split_rdrin);
	while (i < len)
	{
		if (i != 0)
		{
			fd = open_rdirin(data->stack, j);
			j++;
		}
		i++;
	}
	if (fd)
		redirect_cmd(data, split_rdrin[0], fd, 0);
	close(fd);
}
