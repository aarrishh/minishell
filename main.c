/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimanuk <arimanuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:42:23 by arina             #+#    #+#             */
/*   Updated: 2025/07/21 13:51:28 by arimanuk         ###   ########.fr       */
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



void	validation(char **line, t_stack **stack)
{
	t_stack *node;
	int cur_ind;
	int fix_ind;
	int	i;
	int	j;

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
				node = create_node((ft_substr(line[i], j, ft_strlen(line[i]) - cur_ind)));
				add_back(node, stack);
				break;
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
	t_stack *tmp = *stack;
	while (tmp)
	{
		printf("listy exac->  %s\n", (tmp)->string);
		(tmp) = (tmp)->next;
	}
}

void	print_matrix(char **str)
{
	int i = 0;
	while (str[i])
		printf("str->%s\n", str[i++]);
}

void	quotes_check(t_stack *stack, t_info *info)
{
	int		i;
	t_stack	*tmp;

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

void	free_stack(t_stack **stack)
{
	t_stack *tmp;

	tmp = *stack;
	while (tmp)
	{
		tmp = tmp->next;
		free(*stack);
		*stack = tmp;
	}
}

int main(void)
{
	char	*line;
	char	**split;
	t_stack	*stack;
	t_info	info;

	stack = NULL;
	while ((line = readline("minishell$ ")) != NULL)
	{
		if (*line)
			add_history(line);
		split = ft_split(line);
		validation(split, &stack);
		init_info(&info);
		quotes_check(stack, &info);
		// prinit_matrix(split);
		free_stack(&stack);
	}
	return 0;
}
