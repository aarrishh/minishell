/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 12:34:44 by mabaghda          #+#    #+#             */
/*   Updated: 2025/08/13 12:43:13 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	len_by_pipe(t_token **stack)
{
	t_token	*tmp;
	int		len;

	len = 0;
	tmp = *stack;
	while (tmp)
	{
		if (tmp->type == PIPE)
			len++;
		tmp = tmp->next;
	}
	return (len);
}

char	**split_pipe(t_token **stack)
{
	t_token	*tmp;
	int		i;
	char	**commands;
	char	*to_free;
	char	*joined;

	tmp = *stack;
	commands = malloc(sizeof(char *) * (len_by_pipe(stack) + 2));
	if (!commands)
		return (NULL);
	i = 0;
	commands[i] = ft_strdup("");
	while (tmp)
	{
		if (tmp->type == PIPE)
		{
			i++;
			commands[i] = ft_strdup("");
		}
		else
		{
			to_free = commands[i];
			joined = ft_strjoin(tmp->string, " ");
			commands[i] = ft_strjoin(commands[i], joined);
			free(to_free);
			free(joined);
		}
		tmp = tmp->next;
	}
	commands[i + 1] = NULL;
	return (commands);
}
