/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:42:23 by arina             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/07/21 17:18:26 by mabaghda         ###   ########.fr       */
=======
/*   Updated: 2025/07/21 20:08:20 by arimanuk         ###   ########.fr       */
>>>>>>> origin/arish
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_matrix(char **str)
{
	int i = 0;
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

int main(void)
{
	char	*line;
	char	**split;
	t_token	*stack;
	t_info	info;

	stack = NULL;
	while ((line = readline("minishell$ ")) != NULL)
	{
		if (*line)
			add_history(line);
		split = ft_split(line);
		validation(split, &stack);
		init_tokens_type(&stack);
		printf("hasavv?\n");
		init_info(&info);
		quotes_check(stack, &info);
		// prinit_matrix(split);
		free_stack(&stack);
	}
	return (0);
}
