/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:07:12 by arina             #+#    #+#             */
/*   Updated: 2025/07/21 18:41:38 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/history.h>
# include <readline/readline.h>
# include <stdlib.h>

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

typedef struct s_info
{
	int				single_quotes;
	int				double_quotes;
	int				back_quotes;
}					t_info;

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

#endif
