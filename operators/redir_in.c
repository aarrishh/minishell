/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 11:26:23 by mabaghda          #+#    #+#             */
/*   Updated: 2025/08/31 21:55:50 by mabaghda         ###   ########.fr       */
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

char	**add_arg_to_cmd(char **cmd_arg, char *str)
{
	int		len;
	char	**new;
	int		i;

	len = 0;
	while (cmd_arg && cmd_arg[len])
		len++;
	new = (char **)malloc(sizeof(char *) * (len + 2));
	i = 0;
	while (i < len)
	{
		new[i] = cmd_arg[i];
		i++;
	}
	new[i] = str;
	new[i + 1] = NULL;
	free(cmd_arg);
	return (new);
}

void	redir_in(t_data *data)
{
	t_token	*tmp;
	char	**cmd;
	int		fd;

	tmp = data->stack;
	while (tmp && tmp->type != REDIR_IN)
		tmp = tmp->next;
	cmd = make_arr_command(data->stack, REDIR_IN);
	while (tmp && (tmp->type == WORD || tmp->type == REDIR_IN))
	{
		if (tmp && tmp->type == REDIR_IN && tmp->next
			&& tmp->next->type == WORD)
		{
			tmp = tmp->next;
			while (tmp && tmp->next && tmp->next->type == WORD)
			{
				cmd = add_arg_to_cmd(cmd, tmp->next->string);
				tmp = tmp->next;
			}
		}
		if (tmp->type == REDIR_IN && tmp->next == NULL)
		{
			printf("minishell: syntax error near unexpected token `newline'\n");
			g_exit_status = 2;
			return ;
		}
		if (tmp->type == REDIR_IN && tmp->next->type == REDIR_IN)
		{
			printf("minishell: syntax error near unexpected token `<'\n");
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
