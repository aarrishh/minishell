/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 19:50:05 by mabaghda          #+#    #+#             */
/*   Updated: 2025/09/12 22:13:15 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exec_external_command(t_data *data, char **cmd)
{
	char	*path;
	char	**envp;

	envp = env_to_envp(data->env);
	path = split_path(&data->env, cmd[0]);
	if (!path)
		exit(127);
	if (execve(path, cmd, envp) == -1)
	{
		perror("minishell: execve");
		free_array(envp);
		free_array(cmd);
		free(path);
		exit(1);
	}
	free(path);
	exit(1);
}

int	two_dim_len(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

// char	**make_command_pipe(t_token *stack)
// {
// 	t_token	*tmp;
// 	char	**cmd;
// 	int		len;
// 	int		i;

// 	len = 0;
// 	i = 0;
// 	tmp = stack;
// 	while (tmp && tmp->type != PIPE)
// 	{
// 		len++;
// 		tmp = tmp->next;
// 	}
// 	cmd = (char **)malloc(sizeof(char *) * (len + 1));
// 	tmp = stack;
// 	while (i < len && tmp && tmp->type != PIPE)
// 	{
// 		cmd[i] = ft_strdup(tmp->string);
// 		if (!cmd[i])
// 			free_array(cmd);
// 		tmp = tmp->next;
// 		i++;
// 	}
// 	cmd[i] = NULL;
// 	return (cmd);
// }

char	*get_first_word(t_token *tmp)
{
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == WORD)
			return (tmp->string);
		if (tmp->type == REDIR_IN || tmp->type == REDIR_OUT
			|| tmp->type == APPEND || tmp->type == HEREDOC)
		{
			if (tmp->next)
				tmp = tmp->next;
		}
		tmp = tmp->next;
	}
	return ("");
}

int	count_segments(t_token **stack, t_token_type type)
{
	int		len;
	t_token	*tmp;

	tmp = *stack;
	len = 0;
	while (tmp)
	{
		if (tmp->type == type)
			len++;
		tmp = tmp->next;
	}
	return (len + 1);
}
