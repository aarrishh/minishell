/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimanuk <arimanuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 15:24:33 by arina             #+#    #+#             */
/*   Updated: 2025/08/21 15:35:15 by arimanuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pwd_command(void)
{
	char	*dest;

	dest = getcwd(NULL, 0);
	if (!dest)
		return ;
	printf("%s\n", dest);
	free (dest);
	g_exit_status = 0;
}
