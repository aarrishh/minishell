/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arina <arina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 17:59:39 by arimanuk          #+#    #+#             */
/*   Updated: 2025/09/13 17:43:16 by arina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_tokens_type(t_token **stack)
{
	t_token	*tmp;

	tmp = *stack;
	if (!tmp)
		return ;
	while (tmp)
	{
		if (tmp->quote == 0)
		{
			check_type_pipe(tmp->string, &tmp);
			check_type_red_in(tmp->string, &tmp);
			check_type_red_out(tmp->string, &tmp);
			check_type_heredoc(tmp->string, &tmp);
			check_type_append(tmp->string, &tmp);
		}
		tmp = tmp->next;
	}
}

int	check_string(char *str)
{
	int				i;
	t_quote_state	state;

	i = 0;
	state = NO_QUOTE;
	while (str[i])
	{
		state = quote_state(state, str[i]);
		if (state == NO_QUOTE)
		{
			if (str[i] == '>' && str[i + 1] == '>')
				return (-2);
			if (str[i] == '<' && str[i + 1] == '<')
				return (-2);
			if (str[i] == '>' || str[i] == '<' || str[i] == '|'
				|| str[i] == '&')
				return (i);
		}
		i++;
	}
	return (-1);
}

t_token	*if_cur_ind_equal_minus_one(t_val *val, char **line, t_env **env)
{
	t_token	*node;

	val->substr = ft_substr(line[val->i], val->j, ft_strlen(line[val->i])
			- val->j);
	val->expanded = expand_quotes(val->substr, env);
	if (ft_strcmp(val->expanded, "") == 0)
	{
		free(val->substr);
		free(val->expanded);
		val->j += val->cur_ind;
		return (NULL);
	}
	free(val->substr);
	node = create_node(val->expanded);
	node->quote = 1;
	return (node);
}

void	for_all_cases(t_val *val, char **line, t_env **env, t_token **stack)
{
	t_token	*node;

	val->substr = ft_substr(line[val->i], val->j, val->cur_ind);
	val->expanded = expand_quotes(val->substr, env);
	if (ft_strcmp(val->expanded, "") == 0)
	{
		free(val->substr);
		free(val->expanded);
		val->j += val->cur_ind;
		return ;
	}
	free(val->substr);
	node = create_node(val->expanded);
	add_back(node, stack);
	val->j += val->cur_ind;
}

void	validation(char **line, t_token **stack, t_env **env)
{
	t_val	val;

	val.i = 0;
	while (line[val.i])
	{
		val.j = 0;
		while (line[val.i][val.j])
		{
			val.cur_ind = check_string(line[val.i] + val.j);
			if (val.cur_ind == -1)
			{
				add_back(if_cur_ind_equal_minus_one(&val, line, env), stack);
				break ;
			}
			if (val.cur_ind == -2)
				val.cur_ind = 2;
			else if (val.cur_ind == 0)
				val.cur_ind = 1;
			for_all_cases(&val, line, env, stack);
		}
		val.i++;
	}
}
