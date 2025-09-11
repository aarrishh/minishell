/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_helpers1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 13:53:24 by mabaghda          #+#    #+#             */
/*   Updated: 2025/09/11 22:53:52 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	keep_char(t_new_line *line_struct)
{
	line_struct->new[line_struct->j] = line_struct->line[line_struct->i];
	(line_struct->i)++;
	(line_struct->j)++;
}

int	key_len(char *str)
{
	int	len;

	len = 0;
	while (str[len] && (str[len] == '_' || (str[len] >= 'A' && str[len] <= 'Z')
			|| (str[len] >= 'a' && str[len] <= 'z') || (str[len] >= '0'
				&& str[len] <= '9')))
		len++;
	return (len);
}

t_quote_state	quote_state(t_quote_state quote, char c)
{
	if (quote == NO_QUOTE)
	{
		if (c == '\'')
			return (IN_SINGLE);
		if (c == '"')
			return (IN_DOUBLE);
	}
	else if (quote == IN_SINGLE && c == '\'')
		return (NO_QUOTE);
	else if (quote == IN_DOUBLE && c == '"')
		return (NO_QUOTE);
	return (quote);
}

int	is_quote_closed(char *line)
{
	t_quote_state	new_state;
	int				i;

	new_state = NO_QUOTE;
	i = 0;
	while (line[i])
	{
		new_state = quote_state(new_state, line[i]);
		i++;
	}
	return (new_state == NO_QUOTE);
}

void	keep_value(char *new, char *value, int *j)
{
	int	a;

	a = 0;
	while (value[a])
	{
		new[*j] = value[a];
		a++;
		(*j)++;
	}
}
