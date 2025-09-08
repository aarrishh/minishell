/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_helpers2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arina <arina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:16:09 by mabaghda          #+#    #+#             */
/*   Updated: 2025/09/06 16:29:16 by arina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "quotes.h"

void	expand_exit_status(char *new, t_iter *ij)
{
	char	*status_str;
	int		a;

	status_str = ft_itoa(g_exit_status);
	if (!status_str)
		return ;
	a = 0;
	while (status_str[a])
		new[ij->j++] = status_str[a++];
	free(status_str);
	ij->i += 2;
}

void	handle_dollar(char *line, char *new, t_iter *ij, t_env **env)
{
	char	*value;
	int		key_len;

	if (line[ij->i] == '$' && line[ij->i + 1] == '?')
	{
		expand_exit_status(new, ij);
		return ;
	}
	// value = find_var_value(line + ij->i, env, &key_len);
	// if (key_len == 1)
	// {
	// 	new[ij->j] = line[ij->i];
	// 	(ij->i)++;
	// 	(ij->j)++;
	// }
	// if (value)
	// {
	// 	keep_value(new, value, &ij->j);
	// 	ij->i += key_len;
	// }
	// else
	// 	keep_char(line, new, ij);
	value = find_var_value(line + ij->i, env, &key_len);
	if (value == NULL)
	{
		new[ij->j++] = line[ij->i++];
		return ;
	}
	if (value[0] != '\0')
		keep_value(new, value, &ij->j);
	ij->i += key_len;
}

void	exp_help_loop(t_quote_state state, char *str, char *new, t_iter *ij,
		t_env **env)
{
	(ij->i)++;
	if (state == IN_SINGLE)
	{
		while (str[ij->i] && str[ij->i] != '\'')
		{
			new[ij->j] = str[ij->i];
			(ij->i)++;
			(ij->j)++;
		}
		if (str[ij->i] == '\'')
			(ij->i)++;
	}
	else if (state == IN_DOUBLE)
	{
		while (str[ij->i] && str[ij->i] != '"')
			if (str[ij->i] == '$')
				handle_dollar(str, new, ij, env);
			else
				keep_char(str, new, ij);
		if (str[ij->i] == '"')
			(ij->i)++;
	}
}

int	check_valid_dollar(char chr)
{
	return (chr == '_' || (chr >= 'A' && chr <= 'Z') || (chr >= 'a'
			&& chr <= 'z') || (chr >= '0' && chr <= '9'));
}

char	*find_var_value(char *str, t_env **env, int *key_length)
{
	t_env	*tmp;
	int		len;

	if (!str || *str != '$')
	{
		*key_length = 0;
		return (NULL);
	}
	*key_length = 1;
	tmp = *env;
	str++;
	if (!*str)
	{
		*key_length = 1;
		return (NULL);
	}
	if (!check_valid_dollar(*str))
	{
		*key_length = 1;
		return (NULL);
	}
	if (*str >= '0' && *str <= '9')
	{
		*key_length = 2;
		return ("");
	}
	len = key_len(str);
	while (tmp)
	{
		if ((ft_strlen(tmp->key) == len) && (ft_strncmp(str, tmp->key,
					len) == 0))
		{
			*key_length = len + 1;
			return (tmp->value);
		}
		tmp = tmp->next;
	}
	*key_length = len + 1;
	return ("");
}
