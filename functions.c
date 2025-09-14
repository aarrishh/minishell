/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 18:28:46 by arimanuk          #+#    #+#             */
/*   Updated: 2025/09/14 13:01:58 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
		i++;
	return (i);
}

int	length(int n)
{
	int	count;

	count = 0;
	if (n < 10)
		return (1);
	count = 1;
	while (n > 0)
	{
		n /= 10;
		count++;
	}
	return (count);
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

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

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

int	check_long_number(long long *res, int sign, char c)
{
	int	digit;

	digit = c - '0';
	if (sign == 1 && (*res) > (LLONG_MAX - digit) / 10)
		return (-1);
	if (sign == -1 && -(*res) < (LLONG_MIN + digit) / 10)
		return (-1);
	(*res) = (*res) * 10 + digit;
	return (0);
}

int	ft_atol(const char *str, long long *result)
{
	int			i;
	int			sign;
	long long	res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (!ft_isdigit(str[i]))
		return (-1);
	while (ft_isdigit(str[i]))
	{
		if (check_long_number(&res, sign, str[i++]) == -1)
			return (-1);
	}
	if (str[i] != '\0')
		return (-1);
	*result = res * sign;
	return (0);
}

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0')
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
