/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 11:26:23 by mabaghda          #+#    #+#             */
/*   Updated: 2025/09/04 12:44:47 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_rdirin(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror(filename);
		return (0);
	}
	return (fd);
}

char	**add_arg_to_cmd(char **cmd_arg, char *str)
{
	int		len;
	char	**new;
	int		i;

	if (!str)
		return (cmd_arg);
	len = 0;
	i = 0;
	new = NULL;
	if (cmd_arg)
	{
		while (cmd_arg[len])
			len++;
		new = (char **)malloc(sizeof(char *) * (len + 2));
		if (!new)
			return (NULL);
		while (i < len)
		{
			new[i] = ft_strdup(cmd_arg[i]);
			if (!new[i])
				return (free_array(new), NULL);
			i++;
		}
		new[i] = ft_strdup(str);
		if (!new[i])
			return (free_array(new), NULL);
		new[i + 1] = NULL;
		// free_array(cmd_arg);
	}
	else
	{
		new = (char **)malloc(sizeof(char *) * 2);
		if (!new)
			return (NULL);
		new[0] = ft_strdup(str);
		if (!new[0])
		{
			free(new);
			return (NULL);
		}
		new[1] = NULL;
	}
	return (new);
}

void	operators(t_data *data, t_token *stack)
{
	t_command	cmd_struct;

	cmd_struct.cmd_input = 0;
	cmd_struct.cmd_output = 1;
	cmd_struct.cmd = NULL;
	ban_em_pordzum(data, stack, &cmd_struct);
}

void	ban_em_pordzum(t_data *data, t_token *stack, t_command *cmd_struct)
{
	t_token	*tmp;
	int		i;
	char	**tmp_cmd;

	i = 0;
	tmp = stack;
	cmd_struct->cmd = NULL;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == WORD)
		{
			tmp_cmd = add_arg_to_cmd(cmd_struct->cmd, tmp->string);
			if (!tmp_cmd)
			{
				free_array(cmd_struct->cmd);
				perror("malloc failed");
				g_exit_status = 1;
				return ;
			}
			cmd_struct->cmd = tmp_cmd;
		}
		else if (tmp->type == REDIR_IN && tmp->next && tmp->next->type == WORD)
		{
			if (cmd_struct->cmd_input != 0)
				close(cmd_struct->cmd_input);
			cmd_struct->cmd_input = open_rdirin(tmp->next->string);
			tmp = tmp->next;
		}
		else if (tmp->type == REDIR_OUT && tmp->next && tmp->next->type == WORD)
		{
			cmd_struct->cmd_output = find_and_open(tmp->next->string, 0);
			tmp = tmp->next;
		}
		else if (tmp->type == APPEND && tmp->next && tmp->next->type == WORD)
		{
			cmd_struct->cmd_output = find_and_open(tmp->next->string, 1);
			tmp = tmp->next;
		}
		else if (tmp->type == HEREDOC && tmp->next && tmp->next->type == WORD)
		{
			handle_heredoc(data, cmd_struct, tmp, i);
			i++;
			tmp = tmp->next;
		}
		else
		{
			if (tmp->next)
				error_nl_or_type(tmp->next->type);
			else
				error_nl_or_type(0);
			return ;
		}
		tmp = tmp->next;
	}
	execute_command(data, cmd_struct);
	free_array(cmd_struct->cmd);
	cmd_struct->cmd_input = 0;
	cmd_struct->cmd_output = 1;
}

void	error_nl_or_type(t_token_type type)
{
	char *str;

	str = NULL;
	if (!type)
		str = ft_strdup("newline");
	else if (type == REDIR_IN)
		str = ft_strdup("<");
	else if (type == REDIR_OUT)
		str = ft_strdup(">");
	else if (type == APPEND)
		str = ft_strdup(">>");
	printf("minishell: syntax error near unexpected token `%s'\n",
			str);
	free(str);
	g_exit_status = 2;
}