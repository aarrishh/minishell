/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_len1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arina <arina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 10:30:46 by arina             #+#    #+#             */
/*   Updated: 2025/09/14 10:31:21 by arina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "quotes.h"

t_quote_state	handle_double_quote_len(char *line, int *i, int *len,
		t_env **env)
{
	(*i)++;
	while (line[*i] && line[*i] != '"')
	{
		if (line[*i] == '$')
			handle_len_dollar(line, i, len, env);
		else
		{
			(*len)++;
			(*i)++;
		}
	}
	if (line[*i] == '"')
		(*i)++;
	return (NO_QUOTE);
}

int	len_without_quote(char *line, t_quote_state state)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (line[i])
	{
		if (state == IN_SINGLE && line[i] == '\'')
			i++;
		else if (state == IN_DOUBLE && line[i] == '"')
			i++;
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}
