/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 11:26:23 by mabaghda          #+#    #+#             */
/*   Updated: 2025/09/01 18:46:02 by mabaghda         ###   ########.fr       */
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
	i = 0;
	new = NULL;
	if (cmd_arg)
	{
		while (cmd_arg && cmd_arg[len])
			len++;
		new = (char **)malloc(sizeof(char *) * (len + 2));
		if (!new)
			return (NULL);
		while (i < len)
		{
			new[i] = cmd_arg[i];
			i++;
		}
		new[i] = ft_strdup(str);
		new[i + 1] = NULL;
		free(cmd_arg);
	}
	else
	{
		new = (char **)malloc(sizeof(char *) * 2);
		if (!new)
			return (NULL);
		new[0] = ft_strdup(str);
		new[1] = NULL;
	}
	return (new);
}

void	redir_in(t_data *data)
{
	t_token	*tmp;
	char	**cmd;
	int		fd;
	char	*str;
	int		i;

	fd = 0;
	tmp = data->stack;
	cmd = make_arr_command(data->stack, REDIR_IN);
	while (tmp && tmp->type != REDIR_IN)
		tmp = tmp->next;
	while (tmp && (tmp->type == WORD || tmp->type == REDIR_IN))
	{
		if (tmp && tmp->type == REDIR_IN && tmp->next
			&& tmp->next->type == WORD)
		{
			if (fd)
				close(fd);
			fd = open_rdirin(tmp->next->string);
			if (!fd)
			{
				printf("%s: No such file or directory\n", tmp->next->string);
				return ;
			}
			tmp = tmp->next;
		}
		else if (tmp && tmp->type == REDIR_IN && (tmp->next == NULL
				|| tmp->next->type == REDIR_IN))
		{
			if (tmp->next == NULL)
				str = ft_strdup("newline");
			else
				str = ft_strdup("<");
			printf("minishell: syntax error near unexpected token `%s'\n", str);
			g_exit_status = 2;
			free(str);
			return ;
		}
		i = 2;
		while (tmp && tmp->type == WORD && tmp->next && tmp->next->type == WORD)
		{
			cmd = add_arg_to_cmd(cmd, tmp->next->string);
			tmp = tmp->next;
			i++;
		}
		tmp = tmp->next;
	}
	redirect_cmd(data, cmd, fd, 0);
	close(fd);
}

// else if (tmp && tmp->type == REDIR_IN && tmp->next
// 	&& tmp->next->type == REDIR_IN)
// {
// 	// if (tmp->next == NULL)
// 	// 	str = ft_strdup("newline");
// 	// else
// 	// 	str = ft_strdup("<");
// 	printf("minishell: syntax error near unexpected token `<'\n");
// 	g_exit_status = 2;
// 	// free(str);
// 	return ;
// }