/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tokens_type.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arina <arina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 20:52:24 by arina             #+#    #+#             */
/*   Updated: 2025/08/29 14:17:15 by arina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_type_pipe(char *str, t_token **stack)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|')
			(*stack)->type = PIPE;
		i++;
	}
}

void	check_type_red_in(char *str, t_token **stack)
{
	int	i;

	i = 0;
	while (str[i] && !str[i + 1])
		if (str[i++] == '<')
			(*stack)->type = REDIR_IN;
}

void	check_type_red_out(char *str, t_token **stack)
{
	int	i;

	i = 0;
	while (str[i] && !str[i + 1])
		if (str[i++] == '>')
			(*stack)->type = REDIR_OUT;
}

void	check_type_heredoc(char *str, t_token **stack)
{
	int	i;

	i = 0;
	while (str[i] && str[i + 1])
	{
		if (str[i] == '<' && str[i + 1] == '<')
			(*stack)->type = HEREDOC;
		i++;
	}
}

void	check_type_append(char *str, t_token **stack)
{
	int	i;

	i = 0;
	while (str[i] && str[i + 1])
	{
		if (str[i] == '>' && str[i + 1] == '>')
			(*stack)->type = APPEND;
		i++;
	}
}
