/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 17:19:01 by mabaghda          #+#    #+#             */
/*   Updated: 2025/07/21 17:19:46 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int		fix_ind;
	int		i;
	int		j;
	t_token	*tmp;

	i = 0;
	cur_ind = 0;
	fix_ind = 0;
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
	tmp = *stack;
	while (tmp)
	{
		printf("listy exac->  %s\n", (tmp)->string);
		(tmp) = (tmp)->next;
	}
}

void	print_matrix(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		printf("str->%s\n", str[i++]);
}

void	quotes_check(t_token *stack, t_info *info)
{
	int		i;
	t_token	*tmp;

	tmp = stack;
	while (tmp)
	{
		i = 0;
		while (tmp->string[i])
		{
			if (tmp->string[i] == '\"')
				info->double_quotes++;
			else if (tmp->string[i] == '\'')
				info->single_quotes++;
			else if (tmp->string[i] == '`')
				info->back_quotes++;
			i++;
		}
		tmp = tmp->next;
	}
	if (info->back_quotes % 2 != 0 || info->double_quotes % 2 != 0
		|| info->single_quotes % 2 != 0)
	{
		printf("Error\n");
	}
}

void	init_info(t_info *info)
{
	info->back_quotes = 0;
	info->double_quotes = 0;
	info->single_quotes = 0;
}

void	free_stack(t_token **stack)
{
	t_token *tmp;

	tmp = *stack;
	while (tmp)
	{
		tmp = tmp->next;
		free(*stack);
		*stack = tmp;
	}
}