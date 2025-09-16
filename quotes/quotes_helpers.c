/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 22:53:41 by mabaghda          #+#    #+#             */
/*   Updated: 2025/09/16 17:35:21 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_valid_dollar(char chr)
{
	return (chr == '_' || (chr >= 'A' && chr <= 'Z') || (chr >= 'a'
			&& chr <= 'z'));
}

void	error_msg(char *str)
{
	char	*tmp;

	tmp = ft_strjoin(str, ": command not found\n");
	if (!tmp)
		return ;
	ft_putstr_fd(tmp, 2);
	free(tmp);
	g_exit_status = 127;
}

void	error_msg_dir(char *str)
{
	char	*tmp;

	tmp = ft_strjoin(str, ": No such file or directory\n");
	if (!tmp)
		return ;
	ft_putstr_fd(tmp, 2);
	free(tmp);
	g_exit_status = 127;
}

int	get_operator_length(char *s)
{
	if ((s[0] == '<' && s[1] == '<')
		|| (s[0] == '>' && s[1] == '>'))
		return (2);
	return (1);
}
