/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 12:31:19 by mabaghda          #+#    #+#             */
/*   Updated: 2025/01/27 13:35:48 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*tmp;
	size_t			a;

	a = 0;
	tmp = malloc(count * size);
	if (!tmp)
		return (NULL);
	while (a < count * size)
		tmp[a++] = '\0';
	return (tmp);
}
