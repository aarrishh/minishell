/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 12:32:07 by mabaghda          #+#    #+#             */
/*   Updated: 2025/02/03 16:21:09 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	length(int n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		count = 1;
		n = -n;
	}
	while (n > 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*str;

	len = length(n);
	if (n == 0)
		return (ft_strdup("0"));
	else if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	str[len] = '\0';
	while (n > 0)
	{
		str[len-- -1] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}
/*#include <stdio.h>

int	main(void)
{
	char	*res;

	res = ft_itoa(10);
	printf("%s\n", res);
	free(res);
}*/
