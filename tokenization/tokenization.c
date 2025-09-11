/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 17:59:39 by arimanuk          #+#    #+#             */
/*   Updated: 2025/09/11 16:50:25 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_tokens_type(t_token **stack)
{
	t_token	*tmp;

	tmp = *stack;
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

void	validation(char **line, t_token **stack, t_env **env)
{
	t_token	*node;
	int		cur_ind;
	char	*substr;
	char	*expanded;

	int i, j;
	i = 0;
	while (line[i])
	{
		j = 0;
		while (line[i][j])
		{
			cur_ind = check_string(line[i] + j);
			if (cur_ind == -1)
			{
				substr = ft_substr(line[i], j, ft_strlen(line[i]) - j);
				expanded = expand_quotes(substr, env);
				free(substr);
				node = create_node(expanded);
				node->quote = 1;
				add_back(node, stack);
				break ;
			}
			if (cur_ind == -2)
				cur_ind = 2;
			else if (cur_ind == 0)
				cur_ind = 1;
			substr = ft_substr(line[i], j, cur_ind);
			expanded = expand_quotes(substr, env);
			free(substr);
			node = create_node(expanded);
			add_back(node, stack);
			j += cur_ind;
		}
		i++;
	}
}
