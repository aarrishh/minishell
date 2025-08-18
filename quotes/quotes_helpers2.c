/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_helpers2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:16:09 by mabaghda          #+#    #+#             */
/*   Updated: 2025/08/18 15:41:45 by mabaghda         ###   ########.fr       */
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
		return;
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
	int		a;

	a = 0;
	if (line[ij->i] == '$' && line[ij->i + 1] == '?')
	{
		expand_exit_status(new, ij);
		return ;
	}
	value = find_var_value(line + ij->i, env, &key_len);
	if (value)
	{
		if ((check_after_key(line[ij->i + key_len])))
		{
			ij->i += key_len;
			while (line[ij->i] && check_after_key(line[ij->i]))
				ij->i++;
			return ;
		}
		while (value[a])
		{
			new[ij->j] = value[a];
			a++;
			(ij->j)++;
		}
		ij->i += key_len;
	}
	else
	{
		new[ij->j] = line[ij->i];
		(ij->i)++;
		(ij->j)++;
	}
}

void	dquote_expansion(char *line, char *new, t_iter *ij, t_env **env)
{
	char	*value;
	int		key_len;

	if (line[ij->i] == '$')
	{
		value = find_var_value(line + ij->i, env, &key_len);
		if (value)
		{
			if ((check_after_key(line[ij->i + key_len])))
			{
				ij->i += key_len;
				while (line[ij->i] && check_after_key(line[ij->i]))
					ij->i++;
			}
			else
			{
				keep_value(new, value, &ij->j);
				ij->i += key_len;
			}
		}
		else
			keep_char(line, new, ij);
	}
	else
	{
		new[ij->j] = line[ij->i];
		(ij->i)++;
		(ij->j)++;
	}
}

void	exp_help_loop(t_quote_state state, char *str, char *new, t_iter *ij, t_env **env)
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
			dquote_expansion(str, new, ij, env);
		if (str[ij->i] == '"')
			(ij->i)++;
	}
}

char	*find_var_value(char *str, t_env **env, int *key_len)
{
	t_env	*tmp;
	int		len;

	tmp = *env;
	*key_len = 1;
	str++;
	while (tmp)
	{
		len = ft_strlen(tmp->key);
		if (ft_strncmp(str, tmp->key, len) == 0)
		{
			*key_len = len + 1;
			return (tmp->value);
		}
		tmp = tmp->next;
	}
	if (ft_strncmp(str, "EMPTY", 5) == 0)
		return ("");
	return (NULL);
}
