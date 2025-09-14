/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arina <arina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 09:07:29 by arina             #+#    #+#             */
/*   Updated: 2025/09/14 10:38:14 by arina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	syntax_error(char *str)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	if (str)
		ft_putstr_fd(str, 2);
	else
		ft_putstr_fd("newline", 2);
	ft_putstr_fd("'\n", 2);
	g_exit_status = 2;
	return (2);
}

static int	check_pipe(t_token *stack)
{
	if (stack->type == PIPE)
	{
		if (!stack->next || stack->next->type == PIPE)
			return (syntax_error(stack->string));
	}
	return (0);
}

static int	check_redir(t_token *stack)
{
	if (stack->type == REDIR_IN || stack->type == REDIR_OUT
		|| stack->type == APPEND || stack->type == HEREDOC)
	{
		if (!stack->next)
			return (syntax_error(NULL));
		if (stack->next->type == PIPE || stack->next->type == REDIR_IN
			|| stack->next->type == REDIR_OUT || stack->next->type == APPEND
			|| stack->next->type == HEREDOC)
			return (syntax_error(stack->next->string));
	}
	return (0);
}

int	check_syntax(t_token *stack)
{
	if (stack->type == PIPE)
	{
		syntax_error(stack->string);
		return (2);
	}
	while (stack)
	{
		if (check_pipe(stack))
			return (2);
		if (check_redir(stack))
			return (2);
		stack = stack->next;
	}
	return (0);
}
