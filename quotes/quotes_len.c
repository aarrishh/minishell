/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_len.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 13:56:51 by mabaghda          #+#    #+#             */
/*   Updated: 2025/08/14 16:45:20 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "quotes.h"

t_quote_state	handle_double_quote_len(char *line, int *i, int *len, t_env **env)
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

void	handle_len_dollar(char *line, int *i, int *len, t_env **env)
{
	char	*value;
	int		key_len;

	value = find_var_value(line + *i, env, &key_len);
	if (value)
	{
		if ((check_after_key(line[*i + key_len])))
		{
			*i += key_len;
			while (line[*i] && check_after_key(line[*i]))
				(*i)++;
		}
		else
		{
			*len += ft_strlen(value);
			*i += key_len;
		}
	}
	else
	{
		(*len)++;
		(*i)++;
	}
}

t_quote_state	handle_single_quote_len(char *line, int *i, int *len)
{
	(*i)++;
	while (line[*i] && line[*i] != '\'')
	{
		(*len)++;
		(*i)++;
	}
	if (line[*i] == '\'')
		(*i)++;
	return (NO_QUOTE);
}

int	len_for_malloc(char *line, t_env **env)
{
	int				i;
	int				len;
	t_quote_state	state;

	i = 0;
	len = 0;
	state = NO_QUOTE;
	while (line[i])
	{
		state = quote_state(state, line[i]);
		if (state == IN_SINGLE)
			state = handle_single_quote_len(line, &i, &len);
		else if (state == IN_DOUBLE)
			state = handle_double_quote_len(line, &i, &len, env);
		else
		{
			if (line[i] == '$')
				handle_len_dollar(line, &i, &len, env);
			else
			{
				len++;
				i++;
			}
		}
	}
	return (len);
}
