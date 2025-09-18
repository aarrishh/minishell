/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 23:00:11 by mabaghda          #+#    #+#             */
/*   Updated: 2025/09/18 18:51:06 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_str_in_str(char *str1, char *str2)
{
	int	i;
	int	j;

	if (!str1 || !str2)
		return (0);
	i = 0;
	while (str1[i])
	{
		j = 0;
		if (str1[i] == str2[j])
		{
			while (str1[i] && str2[j] && str1[i] == str2[j])
			{
				i++;
				j++;
			}
			if (str2[j] == '\0')
				return (1);
			i -= j;
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

int	check_dl(t_new_line *line_st, int *key_len, char *value)
{
	if (*key_len == 0)
	{
		line_st->len++;
		line_st->i++;
		return (0);
	}
	if (*key_len == -1)
	{
		line_st->i++;
		return (0);
	}
	if (value == NULL)
	{
		line_st->len++;
		line_st->i++;
		return (0);
	}
	return (1);
}
