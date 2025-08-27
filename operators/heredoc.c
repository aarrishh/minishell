/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 21:08:04 by mabaghda          #+#    #+#             */
/*   Updated: 2025/08/27 21:03:12 by mabaghda         ###   ########.fr       */
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

char	*create_file(int i, int *fd)
{
	int		fd_0;
	char	*num;
	char	*filename;

	fd_0 = 0;
	filename = NULL;
	num = ft_itoa(i);
	filename = ft_strjoin("/tmp/arish_manan_heredoc_", num);
	free(num);
	fd_0 = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	*fd = fd_0;
	return (filename);
}

char	*read_heredoc_loop(char *delimiter, int i)
{
	char	*filename;
	char	*line;
	int		fd;

	filename = create_file(i, &fd);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			handle_ctrl_d();
			break ;
		}
		if (check_dollar_hd(line))
			line = expand_heredoc(line);
		if (line && delimiter && ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		else
			ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
	return (filename);
}

char	*expand_heredoc(char *line)
{
	return (line);
	//handle_dollar();
}

int	check_dollar_hd(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
			return (1);
		i++;
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
	char	*filename;
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
		if (i != 0)
		{
			pid = fork();
			if (pid == 0)
			{
				if (i == len - 1)
				{
					filename = read_heredoc_loop(split_hd[i], i);
					read_from_file(&data->env, filename, cmd);
					// exit(0);
				}
				else
				{
					read_heredoc_loop(split_hd[i], i);
					exit(0);
				}
			}
			else
				parent_process_handling(pid, &status, cmd);
		}
		i++;
	}
	free_array(split_hd);
	free_array(cmd);
}

//TODO read from file
void	read_from_file(t_env **env, char *filename, char **cmd)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (dup2(fd, 0) == -1)
	{
		// perror("minishell: dup2");
		exit(127);
	}
	close(fd);
	child_process_execution(env, cmd);
	exit(0);
}
