/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimanuk <arimanuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 16:10:26 by arimanuk          #+#    #+#             */
/*   Updated: 2025/09/14 16:14:45 by arimanuk         ###   ########.fr       */
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
	node = create_node(op);
	add_back(node, stack);
	val->j += oplen;
}

void	flush_word_before_op(t_val *val, char **line,
				t_env **env, t_token **stack)
{
	if (val->cur_ind > 0)
		for_all_cases(val, line, env, stack);
}

void	flush_remainder(t_val *val, char **line,
				t_env **env, t_token **stack)
{
	add_back(if_cur_ind_equal_minus_one(val, line, env), stack);
}
