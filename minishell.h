/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:07:12 by arina             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/07/21 18:41:38 by mabaghda         ###   ########.fr       */
=======
/*   Updated: 2025/07/21 20:43:19 by arimanuk         ###   ########.fr       */
>>>>>>> origin/arish
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/history.h>
# include <readline/readline.h>
# include <stdlib.h>

<<<<<<< HEAD
typedef struct s_token
{
	char			*string;
	struct s_token	*next;
}					t_token;

typedef enum s_token_type
{
	WORD,
	S_PIPE,
	RED_IN,
	RED_OUT,
}					t_token_type;
=======
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
>>>>>>> origin/arish

typedef struct s_info
{
	int				single_quotes;
	int				double_quotes;
	int				back_quotes;
}					t_info;

<<<<<<< HEAD
t_token				*create_node(char *res);
char				**ft_split(char const *s);
void				add_back(t_token *node, t_token **a);
char				*ft_substr(char const *s, unsigned int start, size_t len);
int					ft_strlen(const char *str);
char				*ft_strstr(char *str, char *to_find);
int					check_string(char *str);
void				validation(char **line, t_token **stack);
void				print_matrix(char **str);
void				quotes_check(t_token *stack, t_info *info);
void				init_info(t_info *info);
void				free_stack(t_token **stack);
=======

t_token	*create_node(char *res);
char	**ft_split(char const *s);
void	add_back(t_token *node, t_token **a);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strlen(const char *str);
char	*ft_strstr(char *str, char *to_find);
void	validation(char **line, t_token **stack);
void	init_tokens_type(t_token **stack);
# endif
>>>>>>> origin/arish

#endif
