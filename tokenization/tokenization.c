/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arina <arina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 17:59:39 by arimanuk          #+#    #+#             */
/*   Updated: 2025/08/08 20:51:35 by arina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_tokens_type(t_token **stack)
{
	t_token	*tmp;

	tmp = *stack;
	while (tmp)
	{
		check_type_pipe(tmp->string, &tmp);
		check_type_red_in(tmp->string, &tmp);
		check_type_red_out(tmp->string, &tmp);
		check_type_heredoc(tmp->string, &tmp);
		check_type_append(tmp->string, &tmp);
		tmp = tmp->next;
	}
}

int	check_string(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[0] == '>' && str[1] == '>')
			return (-2);
		if (str[i] == '<' && str[i + 1] == '<')
			return (-2);
		if (str[i] == '>' || str[i] == '<' || str[i] == '|' || str[i] == '&')
			return (i);
		i++;
	}
	return (-1);
}

void	validation(char **line, t_token **stack)
{
	t_token	*node;
	int		cur_ind;
	int		i;
	int		j;

	i = 0;
	cur_ind = 0;
	while (line[i])
	{
		j = 0;
		while (line[i][j])
		{
			cur_ind = check_string(line[i] + j);
			if (cur_ind == -1)
			{
				node = create_node((ft_substr(line[i], j, ft_strlen(line[i])
								- cur_ind)));
				add_back(node, stack);
				break ;
			}
			if (cur_ind == -2)
				cur_ind = 2;
			else if (cur_ind == 0)
				cur_ind = 1;
			node = create_node((ft_substr(line[i], j, cur_ind)));
			add_back(node, stack);
			j += cur_ind;
		}
		i++;
	}
}
