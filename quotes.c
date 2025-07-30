/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 17:01:57 by mabaghda          #+#    #+#             */
/*   Updated: 2025/07/30 14:22:26 by mabaghda         ###   ########.fr       */
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
	(void)line;
	if (state == IN_SINGLE)
		printf("Ստեղ չենք բացում, ոնց կա գրում ենք\n");
	// if (line[i] == '_' || (line[i] >= 'A' && line[i] <= 'Z'))
	// {
	// 	while (line[i] >= 'A')
	// 	{
	// 		if (line[i] == '$')
	// 	}
	// }
}

void	start_quotes(char *line, char ***split)
{
	int				i;
	t_quote_state	state;
	char			*expanded;
	char			*quote_line;

	i = 0;
	state = NO_QUOTE;
	while (line[i])
	{
		state = quote_state(state, line[i]);
		i++;
		if (line[i] == '$' && line[i + 1])
			check_var(state, line + i);
	}
	if (state != NO_QUOTE)
	{
		quote_line = open_dquote(state, line);
		if (quote_line)
			exit(printf("%s%s\n", quote_line, ": command not found") && 0);
	}
	if (state == NO_QUOTE)
		expanded = expand_quotes(line);
	*split = ft_split(expanded, ' ');
}

char	*expand_quotes(char *line)
{
	int				i;
	int				j;
	int				len;
	char			*new;
	t_quote_state	state;

	i = 0;
	j = 0;
	state = NO_QUOTE;
	len = urish_len(line);
	new = (char *)malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	while (line[i])
	{
		state = quote_state(state, line[i]);
		if (state == IN_SINGLE)
		{
			i++;
			while (line[i] && line[i] != '\'')
			{
				new[j] = line[i];
				i++;
				j++;
			}
			if (line[i] == '\'')
				i++;
			state = NO_QUOTE;
			continue ;
		}
		if (state == IN_DOUBLE)
		{
			i++;
			while (line[i] && line[i] != '"')
			{
				new[j] = line[i];
				i++;
				j++;
			}
			if (line[i] == '"')
				i++;
			state = NO_QUOTE;
			continue ;
		}
		else
		{
			new[j] = line[i];
			i++;
			j++;
		}
	}
	new[j] = '\0';
	return (new);
}

int	urish_len(char *line)
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
		{
			i++;
			while (line[i] && line[i] != '\'')
			{
				len++;
				i++;
			}
			if (line[i] == '\'')
				i++;
			state = NO_QUOTE;
		}
		else if (state == IN_DOUBLE)
		{
			i++;
			while (line[i] && line[i] != '"')
			{
				len++;
				i++;
			}
			if (line[i] == '"')
				i++;
			state = NO_QUOTE;
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

char	*open_dquote(t_quote_state state, char *line)
{
	char			*next;
	char			*without_quote_line;
	char			*tmp;
	char			*prompt;
	t_quote_state	new_state;
	int				i;

	if (state == IN_SINGLE)
		prompt = "quote> ";
	else if (state == IN_DOUBLE)
		prompt = "dquote> ";
	while (1)
	{
		next = readline(prompt);
		if (!next)
		{
			printf("wrong EOF, close matching quote\n");
			free(line);
			return (NULL);
		}
		tmp = ft_strjoin(line, "\n");
		free(line);
		line = ft_strjoin(tmp, next);
		free(tmp);
		free(next);
		new_state = NO_QUOTE;
		i = 0;
		while (line[i])
		{
			new_state = quote_state(new_state, line[i]);
			i++;
		}
		if (new_state == NO_QUOTE)
			break ;
	}
	without_quote_line = cut_quotes(line, state);
	return (without_quote_line);
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
		if (line[i] == '\'' && state == IN_SINGLE)
			i++;
		else if (line[i] == '"' && state == IN_DOUBLE)
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
