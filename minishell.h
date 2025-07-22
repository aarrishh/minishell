/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimanuk <arimanuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:07:12 by arina             #+#    #+#             */
/*   Updated: 2025/07/21 20:43:19 by arimanuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

typedef enum e_token_type
{
	WORD, // normal word 0
	PIPE, // | 1
	REDIR_IN, // < 2
	REDIR_OUT, // > 3
	HEREDOC, // << 4
	APPEND, // >> 5
	LIM // 6
}	t_token_type;

typedef struct s_token
{
	char			*string;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

typedef struct s_info
{
	int	single_quotes;
	int	double_quotes;
	int	back_quotes;
}	t_info;


t_token	*create_node(char *res);
char	**ft_split(char const *s);
void	add_back(t_token *node, t_token **a);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strlen(const char *str);
char	*ft_strstr(char *str, char *to_find);
void	validation(char **line, t_token **stack);
void	init_tokens_type(t_token **stack);
# endif

