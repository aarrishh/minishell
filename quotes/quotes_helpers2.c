/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_helpers2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:16:09 by mabaghda          #+#    #+#             */
/*   Updated: 2025/09/11 18:46:15 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "quotes.h"

void	expand_exit_status(t_new_line *line_struct)
{
	char	*status_str;
	int		a;

	status_str = ft_itoa(g_exit_status);
	if (!status_str)
		return ;
	a = 0;
	while (status_str[a])
		line_struct->new[line_struct->j++] = status_str[a++];
	free(status_str);
	line_struct->i += 2;
}

void	handle_dollar(t_new_line *line_struct, t_env **env)
{
	char	*value;
	int		key_len;

	if (line_struct->line[line_struct->i] == '$'
		&& line_struct->line[line_struct->i + 1] == '?')
	{
		expand_exit_status(line_struct);
		return ;
	}
	value = find_var_value(line_struct->line + line_struct->i, env, &key_len);
	if (key_len == 1)
		keep_char(line_struct);
	if (value)
	{
		keep_value(line_struct->new, value, &line_struct->j);
		line_struct->i += key_len;
	}
	else
	{
		if (line_struct->line[line_struct->i]
			&& line_struct->line[line_struct->i] != '"')
			keep_char(line_struct);
	}
}

void	exp_help_loop(t_quote_state state, t_new_line *line_struct, t_env **env)
{
	(line_struct->i)++;
	if (state == IN_SINGLE)
	{
		while (line_struct->line && line_struct->line[line_struct->i]
			&& line_struct->line[line_struct->i] != '\'')
			keep_char(line_struct);
		if (line_struct->line[line_struct->i] == '\'')
			(line_struct->i)++;
	}
	else if (state == IN_DOUBLE)
	{
		while (line_struct->line && line_struct->line[line_struct->i]
			&& line_struct->line[line_struct->i] != '"')
		{
			if (line_struct->line[line_struct->i] == '$')
				handle_dollar(line_struct, env);
			else
				keep_char(line_struct);
		}
		if (line_struct->line[line_struct->i] == '"')
			(line_struct->i)++;
	}
}

int	check_valid_dollar(char chr)
{
	return (chr == '_' || (chr >= 'A' && chr <= 'Z') || (chr >= 'a'
			&& chr <= 'z'));
}

char	*search_env_for_key(char *str, int len, t_env *env)
{
	while (env)
	{
		if ((ft_strlen(env->key) == len) && (ft_strncmp(str, env->key,
					len) == 0))
		{
			return (env->value);
		}
		env = env->next;
	}
	return (NULL);
}

char	*find_var_value(char *str, t_env **env, int *key_length)
{
	int		len;
	char	*value;

	if (!str || *str != '$')
	{
		*key_length = 0;
		return (NULL);
	}
	str++;
	if (!*str || !check_valid_dollar(*str))
	{
		*key_length = 1;
		return (NULL);
	}
	len = key_len(str);
	*key_length = len + 1;
	value = search_env_for_key(str, len, *env);
	if (value)
		return (value);
	return ("");
}
