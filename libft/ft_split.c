/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 13:32:31 by mabaghda          #+#    #+#             */
/*   Updated: 2025/02/01 16:32:17 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *str, char c)
{
	int	a;
	int	count;
	int	word;

	a = 0;
	count = 0;
	word = 0;
	while (str[a])
	{
		if (str[a] != c && word == 0)
		{
			word = 1;
			count++;
		}
		else if (str[a] == c)
		{
			word = 0;
		}
		a++;
	}
	return (count);
}

static void	*free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	const char	*new_s;
	char		**arr;
	int			words_count;
	int			i;

	if (!s)
		return (NULL);
	words_count = count_words(s, c);
	arr = (char **)malloc((words_count + 1) * (sizeof(char *)));
	if (!arr)
		return (NULL);
	i = -1;
	while (++i < words_count)
	{
		while (*s == c)
			s++;
		new_s = s;
		while (*s && *s != c)
			s++;
		arr[i] = ft_substr(new_s, 0, s - new_s);
		if (!arr[i])
			return (free_array(arr));
	}
	arr[i] = NULL;
	return (arr);
}

/*#include <stdio.h>
int main(void)
{
	char **arr = ft_split(" waauyfr acerusfs bbfuerb ", ' ');
	printf("%s\n", arr[0]);
	printf("%s\n", arr[1]);
	printf("%s\n", arr[2]);
}*/
