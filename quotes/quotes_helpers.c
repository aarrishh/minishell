/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arina <arina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 22:53:41 by mabaghda          #+#    #+#             */
/*   Updated: 2025/09/14 10:29:44 by arina            ###   ########.fr       */
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
	if (!tmp)
		return ;
	ft_putstr_fd(tmp, 2);
	free(tmp);
	g_exit_status = 127;
}

void	error_msg_dir(char *quote_line)
{
	char	*tmp;

	tmp = ft_strjoin(quote_line, ": No such file or directory\n");
	if (!tmp)
		return ;
	ft_putstr_fd(tmp, 2);
	free(tmp);
	g_exit_status = 127;
}

void	expand_exit_status(t_new_line *line_st)
{
	char	*status_str;
	int		a;

	status_str = ft_itoa(g_exit_status);
	if (!status_str)
		return ;
	a = 0;
	while (status_str[a])
	{
		line_st->new[line_st->j] = status_str[a];
		line_st->j++;
		a++;
	}
	free(status_str);
	line_st->i += 2;
}
