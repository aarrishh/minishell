/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arina <arina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:25:33 by mabaghda          #+#    #+#             */
/*   Updated: 2025/07/29 15:27:03 by arina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

/*#include <ctype.h>
#include <stdio.h>
int	main(void)
{
	int	b = '9';
	printf("%d\n", ft_isdigit(b));
	printf("%d\n", isdigit(b));
}*/
