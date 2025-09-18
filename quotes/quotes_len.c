/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_len.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 13:56:51 by mabaghda          #+#    #+#             */
/*   Updated: 2025/09/18 18:51:54 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "quotes.h"

t_quote_state	handle_double_quote_len(t_new_line *line_st,
		t_quote_state state, t_env **env)
{
	line_st->i++;
	while (line_st->line[line_st->i] && line_st->line[line_st->i] != '"')
	{
		if (line_st->line[line_st->i] == '$')
			handle_len_dollar(line_st, state, env);
		else
		{
			line_st->len++;
			line_st->i++;
		}
	}
	if (line_st->line[line_st->i] == '"')
		(line_st->i)++;
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

void	handle_len_dollar(t_new_line *line_st, t_quote_state state, t_env **env)
{
	char	*value;
	int		key_len;

	if (line_st->line[(line_st->i)] == '$' && line_st->line[(line_st->i)
			+ 1] == '?')
	{
		line_st->i = line_st->i + 2;
		line_st->len = line_st->len + length(g_exit_status);
		return ;
	}
	value = find_var_value(line_st->line + line_st->i, env, &key_len, state);
	if (!check_dl(line_st, &key_len, value))
		return ;
	line_st->len += ft_strlen(value);
	line_st->i += key_len;
}

t_quote_state	handle_single_quote_len(t_new_line *line_st)
{
	line_st->i++;
	while (line_st->line[line_st->i] && line_st->line[line_st->i] != '\'')
	{
		line_st->len++;
		line_st->i++;
	}
	if (line_st->line[line_st->i] == '\'')
		line_st->i++;
	return (NO_QUOTE);
}

int	len_for_malloc(t_new_line *line_st, t_env **env)
{
	t_quote_state	state;

	state = NO_QUOTE;
	while (line_st->line[line_st->i])
	{
		state = quote_state(state, line_st->line[line_st->i]);
		if (state == IN_SINGLE)
			state = handle_single_quote_len(line_st);
		else if (state == IN_DOUBLE)
			state = handle_double_quote_len(line_st, state, env);
		else if (line_st->line[line_st->i] == '$')
			handle_len_dollar(line_st, state, env);
		else
		{
			line_st->len++;
			line_st->i++;
		}
	}
	return (line_st->len);
}
