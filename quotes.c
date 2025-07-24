/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 17:01:57 by mabaghda          #+#    #+#             */
/*   Updated: 2025/07/24 14:26:32 by mabaghda         ###   ########.fr       */
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

void	start_quotes(char *line, char ***split)
{
	int				i;
	t_quote_state	state;
	char *quote_line;

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
		// printf("Ստեղ բացում ենք QUOTE ԵՐԵՎԻ\n");
		quote_line = open_dquote(state, line);
		printf("%s\n", quote_line);
	}
	if (state == NO_QUOTE)
		*split = ft_split(line, ' ');
}

char	*open_dquote(t_quote_state state, char *line)
{
	char			*next;
	char			*tmp;
	char			*prompt;
	t_quote_state	new_state;
	int				i;

	if (state == IN_SINGLE)
		prompt = "QUOTE> ";
	else if (state == IN_DOUBLE)
		prompt = "DQUOTE> ";
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
	return (line);
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