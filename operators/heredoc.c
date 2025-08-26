/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 21:08:04 by mabaghda          #+#    #+#             */
/*   Updated: 2025/08/26 21:15:23 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	keep_delimiter(t_data *data)
// {
// 	t_token	*temp;

// 	temp = data->stack;
// 	while (temp && temp->next)
// 	{
// 		if (temp->type == HEREDOC)
// 			temp->next->type = LIM;
// 		temp = temp->next;
// 	}
// }

// char	*get_lim_value(t_data *data)
// {
// 	t_token	*temp;

// 	temp = data->stack;
// 	while (temp)
// 	{
// 		if (temp->type == LIM)
// 			return (temp->string);
// 		temp = temp->next;
// 	}
// 	return (NULL);
// }

int	create_file(int i)
{
	int		fd;
	char	*num;
	char	*filename;

	fd = 0;
	filename = NULL;
	num = ft_itoa(i);
	filename = ft_strjoin("/tmp/arish_manan_heredoc_", num);
	free(num);
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	free(filename);
	filename = NULL;
	return (fd);
}

int	read_heredoc_loop(char *delimiter, int i)
{
	int		fd;
	char	*line;

	fd = create_file(i);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			handle_ctrl_d();
			break ;
		}
		if (line && delimiter && ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
			exit(0);
		}
		else
			ft_putendl_fd(line, fd);
		free(line);
	}
	return (0);
}

void	handle_heredoc(t_data *data)
{
	int		status;
	char	**split_hd;
	char	**cmd;
	pid_t	pid;
	int		i;
	int		fd;
	int		len;

	// keep_delimiter(data);
	split_hd = split_operator(&data->stack, HEREDOC);
	if (!split_hd)
		return ;
	cmd = ft_split(split_hd[0], ' ');
	len = two_dim_len(split_hd);
	i = 0;
	while (i < len)
	{
		pid = fork();
		if (pid == 0)
		{
			if (i != 0)
				fd = read_heredoc_loop(split_hd[i], i);
			if (i == len - 1)
				read_from_file(&data->env, fd, cmd);
			exit(0);
		}
		else
			parent_process_handling(pid, &status, cmd);
		i++;
	}
	free_array(split_hd);
	free_array(cmd);
}

//TODO read from file
void	read_from_file(t_env **env, int fd, char **cmd)
{
	dup2(fd, 0);
	close(fd);
	child_process_execution(env, cmd);
}
