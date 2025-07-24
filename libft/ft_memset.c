/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:43:39 by mabaghda          #+#    #+#             */
/*   Updated: 2025/01/21 13:31:07 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*tmpr;

	tmpr = (unsigned char *)b;
	while (len > 0)
	{
		*tmpr = (unsigned char)c;
		tmpr++;
		len--;
	}
	return (b);
}
/*#include <stdio.h>
int main()
{
    char buffer[5];
    ft_memset(buffer, 'n', 3);

    size_t i = 0;
    while (i < 5)
    {
        printf("%c", buffer[i]);
        i++;
    }

    return 0;
}*/
