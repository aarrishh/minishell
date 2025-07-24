/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:25:33 by mabaghda          #+#    #+#             */
/*   Updated: 2025/02/03 15:27:54 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int a)
{
	if (a >= '0' && a <= '9')
		return (1);
	return (0);
}
/*#include <ctype.h>
#include <stdio.h>
int	main(void)
{
	int	b = '9';
	printf("%d\n", ft_isdigit(b));
	printf("%d\n", isdigit(b));
}*/
