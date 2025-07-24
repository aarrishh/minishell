/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 13:32:50 by mabaghda          #+#    #+#             */
/*   Updated: 2025/02/03 12:10:13 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *src)
{
	int		a;
	char	*tmp;
	int		len_src;

	a = 0;
	len_src = ft_strlen(src);
	tmp = (char *)malloc(len_src + 1 * sizeof(char));
	if (!tmp)
		return (NULL);
	while (src[a])
	{
		tmp[a] = src[a];
		a++;
	}
	tmp[a] = '\0';
	return (tmp);
}
/*#include <stdio.h>
int main()
{
	 char	str[5] = "barev";
	 char *res = ft_strdup(str);
	 printf("%c", res[0]);
	 printf("%c", res[1]);
	 printf("%c", res[2]);
	 printf("%c", res[3]);
	 printf("%c", res[4]);
	 
}*/
