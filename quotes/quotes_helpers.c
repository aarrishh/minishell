/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 22:53:41 by mabaghda          #+#    #+#             */
/*   Updated: 2025/09/12 21:02:51 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_valid_dollar(char chr)
{
	return (chr == '_' || (chr >= 'A' && chr <= 'Z') || (chr >= 'a'
			&& chr <= 'z'));
}

void	error_msg(char *quote_line)
{
	char	*tmp;

	tmp = ft_strjoin(quote_line, ": command not found\n");
	ft_putstr_fd(tmp, 2);
	free(tmp);
	g_exit_status = 127;
}
