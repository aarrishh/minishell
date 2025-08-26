/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_helpers3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 13:14:18 by mabaghda          #+#    #+#             */
/*   Updated: 2025/08/26 13:27:11 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_words(const char *str, char c)
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

char	**split_for_quotes(char const *s, char c)
{
	const char		*new_s;
	char			**arr;
	int				words_count;
	int				i;
	t_quote_state	state;

	state = NO_QUOTE;
	if (!s)
		return (NULL);
	words_count = count_words(s, c);
	arr = (char **)malloc((words_count + 1) * (sizeof(char *)));
	if (!arr)
		return (NULL);
	i = -1;
	while (++i < words_count)
	{
		state = quote_state(state, *s);
		while (*s == c && state == NO_QUOTE)
		{
			state = quote_state(state, *s);
			s++;
		}
		new_s = s;
		while (*s && (*s != c || (*s == c && state != NO_QUOTE)))
		{
			state = quote_state(state, *s);
			s++;
		}
		arr[i] = ft_substr(new_s, 0, s - new_s);
		if (!arr[i])
		{
			free_array(arr);
			return (NULL);
		}
	}
	arr[i] = NULL;
	return (arr);
}
