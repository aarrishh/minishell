/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:00:45 by mabaghda          #+#    #+#             */
/*   Updated: 2025/02/03 15:36:42 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int a)
{
	return ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z'));
}
/*#include <ctype.h>
#include <stdio.h>

int	main(void)
{
	char b = 'f';
	printf("%d\n", ft_isalpha(b));
	printf("%d\n", isalpha(b));
}*/
