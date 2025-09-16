/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 13:33:46 by mabaghda          #+#    #+#             */
/*   Updated: 2025/01/31 13:34:49 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	char			*new_string;
	unsigned int	a;
	unsigned int	len;

	len = ft_strlen(s);
	new_string = malloc((len + 1) * sizeof(char));
	if (new_string == NULL)
		return (NULL);
	a = 0;
	while (a < len)
	{
		new_string[a] = f(a, s[a]);
		a++;
	}
	new_string[a] = '\0';
	return (new_string);
}
