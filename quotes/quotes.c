/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 13:53:05 by mabaghda          #+#    #+#             */
/*   Updated: 2025/09/11 22:56:26 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	loop(t_new_line *line_struct, t_quote_state state, t_env **env_struct)
{
	while (line_struct->line[line_struct->i])
	{
		state = quote_state(state, line_struct->line[line_struct->i]);
		if (state != NO_QUOTE)
		{
			exp_help_loop(state, line_struct, env_struct);
			state = NO_QUOTE;
			continue ;
		}
		else
		{
			if (line_struct->line[line_struct->i] == '$')
				handle_dollar(line_struct, env_struct);
			else
				keep_char(line_struct);
		}
	}
	line_struct->new[line_struct->j] = '\0';
}

char	*expand_quotes(char *line, t_env **env_struct)
{
	t_new_line		line_struct;
	int				len;
	char			*new;
	t_quote_state	state;

	state = NO_QUOTE;
	len = len_for_malloc(line, env_struct);
	new = (char *)malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	line_struct.line = line;
	line_struct.new = new;
	line_struct.i = 0;
	line_struct.j = 0;
	loop(&line_struct, state, env_struct);
	return (new);
}

int	start_dquotes(char *line, t_data *data)
{
	int				i;
	t_quote_state	state;
	char			*quote_line;

	i = 0;
	state = NO_QUOTE;
	while (line[i])
		state = quote_state(state, line[i++]);
	if (state != NO_QUOTE)
	{
		quote_line = open_dquote(state, line);
		if (!quote_line)
			return (0);
		error_msg(quote_line);
		g_exit_status = 127;
		free(line);
		free(quote_line);
		return (0);
	}
	else if (state == NO_QUOTE)
	{
		data->split = split_for_quotes(line, ' ');
		free(line);
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
