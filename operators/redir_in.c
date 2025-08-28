/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 11:26:23 by mabaghda          #+#    #+#             */
/*   Updated: 2025/08/28 21:24:59 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// char	*find_filename_in(t_token *stack, int i)
// {
// 	int	count;

// 	count = 0;
// 	while (stack)
// 	{
// 		if (stack->type == REDIR_IN)
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

int	open_rdirin(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		// perror("open");
		return (0);
	}
	return (fd);
}

// void	redir_in(t_data *data)
// {
// 	int		fd;
// 	int		len;
// 	int		i;
// 	int		j;
// 	char	**split_rdrin;

// 	i = 0;
// 	j = 0;
// 	fd = 0;
// 	split_rdrin = split_operator(&data->stack, REDIR_IN);
// 	len = two_dim_len(split_rdrin);
// 	while (i < len)
// 	{
// 		printf("split_rdrin[%d]: %s\n", i, split_rdrin[i]);
// 		if (i != 0)
// 		{
// 			if (fd)
// 				close(fd);
// 			fd = open_rdirin(data->stack, j);
// 			j++;
// 		}
// 		i++;
// 	}
// 	if (fd)
// 		redirect_cmd(data, split_rdrin[0], fd, 0);
// 	close(fd);
// }

void	redir_in(t_data *data)
{
	t_token *tmp;
	char *cmd;
	int fd;

	tmp = data->stack;
	cmd = data->stack->string;
	while (tmp)
	{
		if (tmp->type == REDIR_IN && tmp->next)
		{
			while (tmp && tmp->next)
				tmp = tmp->next;
		}
		else if (tmp->type == REDIR_IN && tmp->next == NULL)
		{
			printf("minishell: syntax error near unexpected token `newline'\n");
			g_exit_status = 2;
			return ;
		}
		if (tmp->type == WORD && tmp->next == NULL)
		{
			fd = open_rdirin(tmp->string);
			redirect_cmd(data, cmd, fd, 0);
		}
		tmp = tmp->next;
	}
	close(fd);
}