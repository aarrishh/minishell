/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 21:08:04 by mabaghda          #+#    #+#             */
/*   Updated: 2025/08/26 16:01:06 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	keep_delimiter(t_data *data)
{
	t_token	*temp;

	temp = data->stack;
	while (temp && temp->next)
	{
		if (temp->type == HEREDOC)
			temp->next->type = LIM;
		temp = temp->next;
	}
}

char	*get_lim_value(t_data *data)
{
	t_token	*temp;

	temp = data->stack;
	while (temp)
	{
		if (temp->type == LIM)
			return (temp->string);
		temp = temp->next;
	}
	return (NULL);
}

int	create_file(void)
{
	int		i;
	int		fd;
	char	*num;
	char	*filename;

	i = 1;
	fd = 0;
	filename = NULL;
	num = ft_itoa(i);
	filename = ft_strjoin("/tmp/arish_manan_heredoc_", num);
	free(num);
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	free(filename);
	// i++;
	return (fd);
}

void	handle_heredoc(t_data *data)
{
	int		fd;
	char	*line;

	keep_delimiter(data);
	fd = create_file();
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			handle_ctrl_d();
			break ;
		}
		if (ft_strcmp(line, get_lim_value(data)) == 0)
		{
			free(line);
			break ;
		}
		else
			ft_putendl_fd(line, fd);
	}
	read_from_file(fd);
	close(fd);
}

void	read_from_file(int fd)
{
	;
}