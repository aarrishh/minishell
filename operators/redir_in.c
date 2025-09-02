/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 11:26:23 by mabaghda          #+#    #+#             */
/*   Updated: 2025/09/02 23:34:23 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_rdirin(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		// perror("open");
		return (0);
	}
	return (fd);
}

char	**add_arg_to_cmd(char **cmd_arg, char *str)
{
	int		len;
	char	**new;
	int		i;

	len = 0;
	i = 0;
	new = NULL;
	if (cmd_arg)
	{
		while (cmd_arg && cmd_arg[len])
			len++;
		new = (char **)malloc(sizeof(char *) * (len + 2));
		if (!new)
			return (NULL);
		while (i < len)
		{
			new[i] = cmd_arg[i];
			i++;
		}
		new[i] = ft_strdup(str);
		new[i + 1] = NULL;
		free(cmd_arg);
	}
	else
	{
		new = (char **)malloc(sizeof(char *) * 2);
		if (!new)
			return (NULL);
		new[0] = ft_strdup(str);
		new[1] = NULL;
	}
	return (new);
}

void	redir_in(t_data *data, t_command *cmd_struct)
{
	t_token	*tmp;
	int		fd;
	int		i;

	fd = 0;
	tmp = data->stack;
	cmd_struct->cmd = make_arr_command(data->stack);
	while (tmp && tmp->type == WORD)
		tmp = tmp->next;
	while (tmp && (tmp->type == WORD || tmp->type == REDIR_IN))
	{
		if (tmp && tmp->type == REDIR_IN && tmp->next
			&& tmp->next->type == WORD)
		{
			if (cmd_struct->cmd_input != 0)
				close(cmd_struct->cmd_input);
			cmd_struct->cmd_input = open_rdirin(tmp->next->string);
			if (!cmd_struct->cmd_input)
			{
				printf("%s: No such file or directory\n", tmp->next->string);
				return ;
			}
			tmp = tmp->next;
		}
		else if (tmp && tmp->type == REDIR_IN && (tmp->next == NULL
					|| tmp->next->type == REDIR_IN))
		{
			error_nl_or_type(tmp->next->type);
			g_exit_status = 2;
			return ;
		}
		i = 2;
		while (tmp && tmp->type == WORD && tmp->next && tmp->next->type == WORD)
		{
			cmd_struct->cmd = add_arg_to_cmd(cmd_struct->cmd,
												tmp->next->string);
			tmp = tmp->next;
			i++;
		}
		tmp = tmp->next;
	}
	close(fd);
}

void	operators(t_data *data)
{
	t_command	cmd_struct;
	t_token		*tmp;

	tmp = data->stack;
	cmd_struct.cmd_input = 0;
	cmd_struct.cmd_output = 1;
	cmd_struct.cmd = NULL;
	while (tmp && tmp->type == WORD)
		tmp = tmp->next;
	if (tmp->type == REDIR_IN)
		redir_in(data, &cmd_struct);
	else if (tmp->type == REDIR_OUT || tmp->type == APPEND)
		redir_function(data, &cmd_struct);
	else if (tmp->type == HEREDOC)
		handle_heredoc(data, &cmd_struct);
	execute_command(data, &cmd_struct);
}

void	ban_em_pordzum(t_data *data, t_command *cmd_struct)
{
	t_token *tmp;

	tmp = data->stack;
	cmd_struct->cmd = make_arr_command(data->stack);
	while (tmp)
	{
		tmp = tmp->next;
	}
	
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
}