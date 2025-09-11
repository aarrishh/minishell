/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_helpers3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 13:14:18 by mabaghda          #+#    #+#             */
/*   Updated: 2025/09/11 18:18:58 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	q_count_words(const char *str, char c)
{
	int				a;
	int				count;
	int				word;
	t_quote_state	state;

	a = 0;
	count = 0;
	word = 0;
	state = NO_QUOTE;
	while (str[a])
	{
		state = quote_state(state, str[a]);
		if (str[a] != c && word == 0)
		{
			word = 1;
			count++;
		}
		else if (str[a] == c && state == NO_QUOTE)
			word = 0;
		a++;
	}
	return (count);
}

static const char	*skip_chars(const char *s, char c, t_quote_state *state)
{
	while (*s == c && *state == NO_QUOTE)
	{
		*state = quote_state(*state, *s);
		s++;
	}
	return (s);
}

static const char	*find_end(const char *s, char c, t_quote_state *state)
{
	*state = NO_QUOTE;
	while (*s && (*s != c || *state != NO_QUOTE))
	{
		*state = quote_state(*state, *s);
		s++;
	}
	return (s);
}

char	**split_for_quotes(char const *s, char c)
{
	char			**arr;
	const char		*start;
	int				words_count;
	int				i;
	t_quote_state	state;

	if (!s)
		return (NULL);
	words_count = q_count_words(s, c);
	arr = (char **)malloc((words_count + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	i = -1;
	state = NO_QUOTE;
	while (++i < words_count)
	{
		s = skip_chars(s, c, &state);
		start = s;
		s = find_end(s, c, &state);
		arr[i] = ft_substr(start, 0, s - start);
		if (!arr[i])
			return (free_array(arr), NULL);
	}
	arr[i] = NULL;
	return (arr);
}
