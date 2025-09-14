/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 21:05:26 by mabaghda          #+#    #+#             */
/*   Updated: 2025/09/14 12:30:15 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	has_operator(t_token *stack, t_token_type type)
{
	while (stack)
	{
		if (stack->type == type)
			return (1);
		stack = stack->next;
	}
	return (0);
}

int	open_rdirin(char *filename)
{
	char	*error;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		error = ft_strjoin("minishell: ", filename);
		perror(error);
		free(error);
		g_exit_status = 1;
		return (-1);
	}
	return (fd);
}

char	**add_arg_to_cmd(char **cmd_arg, char *str)
{
	int		len;
	int		i;
	char	**new;

	len = 0;
	i = -1;
	if (!str)
		return (cmd_arg);
	len = two_dim_len(cmd_arg);
	new = (char **)malloc(sizeof(char *) * (len + 2));
	if (!new)
		return (NULL);
	while (++i < len)
	{
		new[i] = ft_strdup(cmd_arg[i]);
		if (!new[i])
			return (free_array(new), NULL);
	}
	new[i] = ft_strdup(str);
	if (!new[i])
		return (free_array(new), NULL);
	new[i + 1] = NULL;
	if (cmd_arg)
		free_array(cmd_arg);
	return (new);
}

char	**add_cmd(t_command *cmd_struct, t_token *tmp)
{
	char	**tmp_cmd;

	tmp_cmd = add_arg_to_cmd(cmd_struct->cmd, tmp->string);
	if (!tmp_cmd)
	{
		free_array(cmd_struct->cmd);
		perror("malloc failed");
		g_exit_status = 1;
		return (NULL);
	}
	return (tmp_cmd);
}

void	error_nl_or_type(t_command *cmd_s, t_token *tmp)
{
	char	*str;

	str = NULL;
	if (!tmp)
		str = ft_strdup("newline");
	else if (tmp->type == REDIR_IN)
		str = ft_strdup("<");
	else if (tmp->type == REDIR_OUT)
		str = ft_strdup(">");
	else if (tmp->type == APPEND)
		str = ft_strdup(">>");
	printf("minishell: syntax error near unexpected token `%s'\n", str);
	free(str);
	g_exit_status = 2;
	cmd_s->execute = -1;
}
