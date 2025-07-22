/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 17:01:57 by mabaghda          #+#    #+#             */
/*   Updated: 2025/07/22 20:29:30 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	check_var(t_quote_state state, char *line)
{
	// int	i;

	// i = 1;
	if (state == IN_SINGLE)
		printf("Ստեղ չենք բացում, ոնց կա գրում ենք %s\n", line);
	// if (line[i] == '_' || (line[i] >= 'A' && line[i] <= 'Z'))
	// {
	// 	while (line[i] >= 'A')
	// 	{
	// 		if (line[i] == '$')
	// 	}
	// }
}

void	start_quotes(char *line)
{
	int				i;
	t_quote_state	state;

	i = 0;
	state = NO_QUOTE;
	while (line[i])
	{
		state = quote_state(state, line[i]);
		i++;
		if (line[i] == '$')
			check_var(state, line + i);
	}
	if (state != NO_QUOTE)
		printf("Ստեղ բացում ենք QUOTE ԵՐԵՎԻ\n");
}

// if (line[i] == '\'' || line[i] == '"' || line[i] == '`')
// {
// 	if (line[i] == '\'' && quotes->single_quotes != 1)
// 	{
// 		quotes->single_quotes = 1;
// 		i++;
// 	}
// 	else if (line[i] == '"' && quotes->double_quotes != 1)
// 	{
// 		quotes->double_quotes = 1;
// 		i++;
// 	}
// 	else if(line[i] == '`' && quotes->back_quotes != 1)
// 	{
// 		quotes->back_quotes = 1;
// 		i++;
// 	}
// 	if (line[i] == '\'' && quotes->single_quotes == 1)
// }