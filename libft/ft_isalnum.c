/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:31:50 by mabaghda          #+#    #+#             */
/*   Updated: 2025/01/27 15:12:27 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
/*int	ft_isalnum(char a)
{
	return ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z')
		|| (a >= '0' && a <= '9'));
}*/

int	ft_isalnum(char a)
{
	return (ft_isdigit(a) || ft_isalpha(a));
}

/*#include <ctype.h>
#include <stdio.h>
int	main(void)
{
	char b = '-';
	printf("%d\n", ft_isalnum(b));
	printf("%d\n", isalnum(b));
}*/
