/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arina <arina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 18:28:46 by arimanuk          #+#    #+#             */
/*   Updated: 2025/07/28 13:09:18 by arina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*a;
	size_t	i;
	size_t	s_len;
	size_t	malloc_len;

	s_len = 0;
	while (s[s_len])
		s_len++;
	if (start > s_len)
		malloc_len = 0;
	else if (start + len > s_len)
		malloc_len = s_len - start;
	else
		malloc_len = len;
	a = (char *)malloc((malloc_len + 1) * sizeof(char));
	if (a == NULL)
		return (NULL);
	i = 0;
	while (i < malloc_len)
	{
		a[i] = s[start + i];
		i++;
	}
	a[i] = '\0';
	return (a);
}

char	*ft_strstr(char *str, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	if (to_find[0] == '\0')
		return (str);
	while (str[i] != '\0')
	{
		j = 0;
		while (to_find[j] != '\0')
		{
			if (str[i] == to_find[j])
			{
				j++;
				i++;
			}
			else
				break ;
		}
		if (to_find[j] == '\0')
			return (str + i - j);
		else
			i -= j - 1;
	}
	return (0);
}

int ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] == s2[i])
			i++;
		else
			return (s1[i] - s2[i]);
	}
	return (0);
}