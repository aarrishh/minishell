/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 21:08:04 by mabaghda          #+#    #+#             */
/*   Updated: 2025/08/23 21:47:53 by mabaghda         ###   ########.fr       */
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

void	handle_heredoc(t_data *data)
{
	char *line;

	keep_delimiter(data);
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
	}
}