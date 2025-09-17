/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 23:00:11 by mabaghda          #+#    #+#             */
/*   Updated: 2025/09/17 23:05:54 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_str_in_str(char *str1, char *str2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str1[i])
	{
		if (str1[i] == str2[j])
		{
			while (str1[i] && str2[j] && (str2[j] == str1[i]))
			{
				i++;
				j++;
			}
			if (str2[j] == '\0')
				return (1);
		}
		i++;
	}
	return (0);
}

void	flush_word_before_op(t_val *val, char **line, t_env **env,
		t_token **stack)
{
	if (val->cur_ind > 0)
		for_all_cases(val, line, env, stack);
}

void	flush_remainder(t_val *val, char **line, t_env **env, t_token **stack)
{
	add_back(if_cur_ind_equal_minus_one(val, line, env), stack);
}
