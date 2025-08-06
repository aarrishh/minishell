/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 17:01:57 by mabaghda          #+#    #+#             */
/*   Updated: 2025/08/06 11:19:40 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_quote_state	quote_state(t_quote_state quote, char c)
{
	if (quote == NO_QUOTE)
	{
		if (c == '\'')
			return (IN_SINGLE);
		if (c == '"')
			return (IN_DOUBLE);
	}
	else if (quote == IN_SINGLE && c == '\'')
		return (NO_QUOTE);
	else if (quote == IN_DOUBLE && c == '"')
		return (NO_QUOTE);
	return (quote);
}

int	start_quotes(char *line, char ***split, t_env **env_struct)
{
	int				i;
	t_quote_state	state;
	char			*expanded;
	char			*quote_line;

	i = 0;
	(void)env_struct;
	state = NO_QUOTE;
	while (line[i])
	{
		state = quote_state(state, line[i]);
		i++;
	}
	if (state != NO_QUOTE)
	{
		quote_line = open_dquote(state, line);
		if (quote_line)
		{
			printf("%s%s\n", quote_line, ": command not found");
			return (0);
		}
	}
	else if (state == NO_QUOTE)
		expanded = expand_quotes(line, env_struct);
	*split = ft_split(expanded, ' ');
	return (1);
}

void	exp_help_loop(t_quote_state state, char *str, char *new, int *i, int *j,
		t_env **env)
{
	char	*value;
	int		a;
	int		key_len;

	(*i)++;
	a = 0;
	key_len = 0;
	if (state == IN_SINGLE)
	{
		while (str[*i] && str[*i] != '\'')
		{
			new[*j] = str[*i];
			(*i)++;
			(*j)++;
		}
		if (str[*i] == '\'')
			(*i)++;
	}
	else if (state == IN_DOUBLE)
	{
		while (str[*i] && str[*i] != '"')
		{
			if (str[*i] == '$')
			{
				value = find_var_value(str + *i, env, &key_len);
				if (value)
				{
					while (value[a])
					{
						new[*j] = value[a];
						a++;
						(*j)++;
					}
					(*i) += key_len;
				}
				else
				{
					new[*j] = str[*i];
					(*i)++;
					(*j)++;
				}
			}
			else
			{
				new[*j] = str[*i];
				(*i)++;
				(*j)++;
			}
		}
		if (str[*i] == '"')
			(*i)++;
	}
}

char	*find_var_value(char *str, t_env **env, int *key_len)
{
	t_env	*tmp;
	int		len;

	tmp = *env;
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
	return (NULL);
}

char	*expand_quotes(char *line, t_env **env_struct)
{
	int				i;
	int				j;
	int				a;
	int				len;
	int				key_len;
	char			*value;
	char			*new;
	t_quote_state	state;

	i = 0;
	j = 0;
	a = 0;
	state = NO_QUOTE;
	len = urish_len(line, env_struct);
	new = (char *)malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	while (line[i])
	{
		state = quote_state(state, line[i]);
		if (state != NO_QUOTE)
		{
			exp_help_loop(state, line, new, &i, &j, env_struct);
			state = NO_QUOTE;
			continue ;
		}
		else
		{
			if (line[i] == '$')
			{
				value = find_var_value(line + i, env_struct, &key_len);
				if (value)
				{
					while (value[a])
					{
						new[j] = value[a];
						a++;
						j++;
					}
					i += key_len;
				}
				else
				{
					new[j] = line[i];
					i++;
					j++;
				}
			}
			else
			{
				new[j] = line[i];
				i++;
				j++;
			}
		}
	}
	new[j] = '\0';
	return (new);
}

int	urish_len(char *line, t_env **env)
{
	char			*value;
	int				i;
	int				len;
	int				key_len;
	t_quote_state	state;

	i = 0;
	len = 0;
	state = NO_QUOTE;
	while (line[i])
	{
		state = quote_state(state, line[i]);
		if (state == IN_SINGLE)
		{
			i++;
			while (line[i] && line[i] != '\'')
			{
				len++;
				i++;
			}
			if (line[i] == '\'')
				i++;
			state = NO_QUOTE;
		}
		else if (state == IN_DOUBLE)
		{
			i++;
			while (line[i] && line[i] != '"')
			{
				if (line[i] == '$')
				{
					value = find_var_value(line + i, env, &key_len);
					if (value)
					{
						len += ft_strlen(value);
						i += key_len;
					}
					else
					{
						len++;
						i++;
					}
				}
				else
				{
					len++;
					i++;
				}
			}
			if (line[i] == '"')
				i++;
			state = NO_QUOTE;
		}
		else
		{
			if (line[i] == '$')
			{
				value = find_var_value(line + i, env, &key_len);
				if (value)
				{
					len += ft_strlen(value);
					i += key_len;
				}
				else
				{
					len++;
					i++;
				}
			}
			else
			{
				len++;
				i++;
			}
		}
	}
	return (len);
}

char	*open_dquote(t_quote_state state, char *line)
{
	char			*next;
	char			*without_quote_line;
	char			*tmp;
	char			*prompt;
	t_quote_state	new_state;
	int				i;

	if (state == IN_SINGLE)
		prompt = "quote> ";
	else if (state == IN_DOUBLE)
		prompt = "dquote> ";
	while (1)
	{
		next = readline(prompt);
		if (!next)
		{
			printf("wrong EOF, close matching quote\n");
			free(line);
			return (NULL);
		}
		tmp = ft_strjoin(line, "\n");
		free(line);
		line = ft_strjoin(tmp, next);
		free(tmp);
		free(next);
		new_state = NO_QUOTE;
		i = 0;
		while (line[i])
		{
			new_state = quote_state(new_state, line[i]);
			i++;
		}
		if (new_state == NO_QUOTE)
			break ;
	}
	without_quote_line = cut_quotes(line, state);
	return (without_quote_line);
}

int	len_without_quote(char *line, t_quote_state state)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (line[i])
	{
		if (state == IN_SINGLE && line[i] == '\'')
			i++;
		else if (state == IN_DOUBLE && line[i] == '"')
			i++;
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

char	*cut_quotes(char *line, t_quote_state state)
{
	int		i;
	int		j;
	int		len;
	char	*new_line;

	i = 0;
	j = 0;
	len = len_without_quote(line, state);
	new_line = (char *)malloc(sizeof(char) * (len + 1));
	if (!new_line)
		return (NULL);
	while (line[i])
	{
		if (line[i] == '\'' && state == IN_SINGLE)
			i++;
		else if (line[i] == '"' && state == IN_DOUBLE)
			i++;
		else
		{
			new_line[j] = line[i];
			i++;
			j++;
		}
	}
	new_line[j] = '\0';
	return (new_line);
}
