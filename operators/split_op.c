/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 12:34:44 by mabaghda          #+#    #+#             */
/*   Updated: 2025/08/28 20:48:42 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	len_by_op(t_token **stack, t_token_type type)
{
	t_token	*tmp;
	int		len;

	len = 0;
	tmp = *stack;
	while (tmp)
	{
		if (tmp->type == type)
			len++;
		tmp = tmp->next;
	}
	return (len);
}

char	**split_operator(t_token **stack, t_token_type type)
{
	t_token	*tmp;
	int		i;
	char	**commands;
	char	*to_free;
	char	*joined;

	tmp = *stack;
	commands = malloc(sizeof(char *) * (len_by_op(stack, type) + 2));
	if (!commands)
		return (NULL);
	i = 0;
	commands[i] = ft_strdup("");
	while (tmp)
	{
		if (tmp->type == type)
		{
			i++;
			commands[i] = ft_strdup("");
		}
		else
		{
			to_free = commands[i];
			if (tmp->next && tmp->next->type != type)
				joined = ft_strjoin(tmp->string, " ");
			else
				joined = ft_strdup(tmp->string);
			commands[i] = ft_strjoin(commands[i], joined);
			free(to_free);
			free(joined);
		}
		tmp = tmp->next;
	}
	commands[i + 1] = NULL;
	return (commands);
}
