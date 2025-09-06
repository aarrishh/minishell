/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_helpers1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 13:53:24 by mabaghda          #+#    #+#             */
/*   Updated: 2025/09/06 12:24:01 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "quotes.h"

void	keep_char(char *line, char *new, t_iter *ij)
{
	new[ij->j] = line[ij->i];
	(ij->i)++;
	(ij->j)++;
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
