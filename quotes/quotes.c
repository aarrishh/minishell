/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 13:53:05 by mabaghda          #+#    #+#             */
/*   Updated: 2025/08/31 17:08:47 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "quotes.h"

void	loop(char *line, char *new, t_quote_state state, t_env **env_struct)
{
	t_iter	ij;

	ij.i = 0;
	ij.j = 0;
	while (line[ij.i])
	{
		state = quote_state(state, line[ij.i]);
		if (state != NO_QUOTE)
		{
			exp_help_loop(state, line, new, &ij, env_struct);
			state = NO_QUOTE;
			continue ;
		}
		else
		{
			if (line[ij.i] == '$')
				handle_dollar(line, new, &ij, env_struct);
			else
				keep_char(line, new, &ij);
		}
	}
	new[ij.j] = '\0';
}

char	*expand_quotes(char *line, t_env **env_struct)
{
	int				len;
	char			*new;
	t_quote_state	state;

	state = NO_QUOTE;
	len = len_for_malloc(line, env_struct);
	new = (char *)malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	loop(line, new, state, env_struct);
	return (new);
}

int	start_quotes(char *line, t_data *data)
{
	int				i;
	int				len;
	t_quote_state	state;
	char			**expanded;
	char			*quote_line;

	i = 0;
	len = 0;
	state = NO_QUOTE;
	expanded = NULL;
	while (line[i])
	{
		state = quote_state(state, line[i]);
		i++;
	}
	if (state != NO_QUOTE)
	{
		quote_line = open_dquote(state, line);
		if (!quote_line)
			return (0);
		printf("%s%s\n", quote_line, ": command not found");
		g_exit_status = 127;
		free(line);
		free(quote_line);
		return (0);
	}
	else if (state == NO_QUOTE)
	{
		data->split = split_for_quotes(line, ' ');
		len = two_dim_len(data->split);
		i = 0;
		expanded = (char **)malloc(sizeof(char *) * (len + 1));
		if (!expanded)
			return (0);
		while (i < len)
		{
			expanded[i] = expand_quotes(data->split[i], &data->env);
			free(data->split[i]);
			i++;
		}
		expanded[i] = NULL;
		free(data->split);
		data->split = expanded;
	}
	return (1);
}

char	*open_dquote(t_quote_state state, char *line)
{
	char	*next;
	char	*without_quote_line;
	char	*tmp;
	char	*prompt;

	if (state == IN_SINGLE)
		prompt = "quote> ";
	else if (state == IN_DOUBLE)
		prompt = "dquote> ";
	while (1)
	{
		next = readline(prompt);
		if (!next)
		{
			g_exit_status = 2;
			return (printf("wrong EOF, close matching quote\n"), NULL);
		}
		tmp = ft_strjoin(line, "\n");
		free(line);
		line = ft_strjoin(tmp, next);
		free(tmp);
		free(next);
		if (is_quote_closed(line))
			break ;
	}
	without_quote_line = cut_quotes(line, state);
	return (without_quote_line);
}

char	*cut_quotes(char *line, t_quote_state state)
{
	int		i;
	int		j;
	int		len;
	char	*new_line;

	i = 0;
	j = 0;
	len = len_without_quote(line, state);
	new_line = (char *)malloc(sizeof(char) * (len + 1));
	if (!new_line)
		return (NULL);
	while (line[i])
	{
		if ((line[i] == '\'' && state == IN_SINGLE) || (line[i] == '"'
				&& state == IN_DOUBLE))
			i++;
		else
		{
			new_line[j] = line[i];
			i++;
			j++;
		}
	}
	new_line[j] = '\0';
	return (new_line);
}
