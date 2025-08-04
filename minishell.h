/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimanuk <arimanuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:07:12 by arina             #+#    #+#             */
/*   Updated: 2025/08/01 12:26:31 by arimanuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <limits.h>

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef enum e_token_type
{
	WORD,      // 0
	PIPE,      // | 1
	REDIR_IN,  // < 2
	REDIR_OUT, // > 3
	HEREDOC,   // << 4
	APPEND,    // >> 5
	LIM        // 6
}	t_token_type;

typedef struct s_token
{
	char			*string;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

typedef enum e_quote_state
{
	NO_QUOTE,
	IN_SINGLE,
	IN_DOUBLE,
}	t_quote_state;

t_token				*create_node(char *res);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strstr(char *str, char *to_find);
void				add_back(t_token *node, t_token **a);
void				validation(char **line, t_token **stack);
void				init_tokens_type(t_token **stack);
void				start_quotes(char *line, char ***split);
void				check_var(char *line);
char				*open_dquote(t_quote_state state, char *line);
char				*cut_quotes(char *line, t_quote_state state);
int					len_without_quote(char *line, t_quote_state state);
char				*expand_quotes(char *line);
int					urish_len(char *line);
int 				ft_strcmp(char *s1, char *s2);
int					ft_strlen(const char *str);
void				built_in_functions(t_token **stack, t_env **env);
int					ft_atol(const char *str, long long *result);
t_env				*add_env_to_list(char **envp);

#endif
