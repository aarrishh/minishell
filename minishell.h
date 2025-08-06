/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:07:12 by arina             #+#    #+#             */
/*   Updated: 2025/08/06 14:34:08 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "quotes/quotes.h"
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdlib.h>

typedef enum e_token_type
{
	WORD,      // 0
	PIPE,      // | 1
	REDIR_IN,  // < 2
	REDIR_OUT, // > 3
	HEREDOC,   // << 4
	APPEND,    // >> 5
	LIM        // 6
}					t_token_type;

typedef struct s_token
{
	char			*string;
	t_token_type	type;
	struct s_token	*next;
}					t_token;

t_token				*create_node(char *res);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strstr(char *str, char *to_find);
void				add_back(t_token *node, t_token **a);
void				validation(char **line, t_token **stack);
void				init_tokens_type(t_token **stack);
int					ft_strcmp(char *s1, char *s2);
int					ft_strlen(const char *str);
void				built_in_functions(t_token **stack, t_env **env);
int					ft_atol(const char *str, long long *result);
t_env				*add_env_to_list(char **envp);

#endif
