/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 16:10:26 by arimanuk          #+#    #+#             */
/*   Updated: 2025/09/17 23:04:58 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	init_cmd(t_command *cmd_struct)
{
	cmd_struct->input = 0;
	cmd_struct->output = 1;
	cmd_struct->execute = 1;
	cmd_struct->heredoc = NULL;
	cmd_struct->cmd = NULL;
}

int	in_set(char *s, char c)
{
	while (*s)
	{
		if (*s == c)
			return (1);
		s++;
	}
	return (0);
}

void	handle_operator(t_val *val, char **line, t_token **stack)
{
	int		oplen;
	char	*op;
	t_token	*node;

	oplen = get_operator_length(line[val->i] + val->j);
	op = ft_substr(line[val->i], val->j, oplen);
	if (is_str_in_str(op, "<<"))
		val->expand = 0;
	node = create_node(&op);
	add_back(node, stack);
	val->j += oplen;
}
