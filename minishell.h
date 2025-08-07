/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:07:12 by arina             #+#    #+#             */
/*   Updated: 2025/08/07 18:45:58 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "pipe/pipe.h"
# include "quotes/quotes.h"

# define PB "\001\033[1;38;2;255;204;213m\002" // bold pink
# define W "\001\033[38;2;255;255;255m\002"    // white
# define R "\001\033[0m\002"                   // reset

t_token	*create_node(char *res);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strstr(char *str, char *to_find);
void	add_back(t_token *node, t_token **a);
void	validation(char **line, t_token **stack);
void	init_tokens_type(t_token **stack);
int		ft_strcmp(char *s1, char *s2);
int		ft_strlen(const char *str);
void	built_in_functions(t_token **stack, t_env **env);
int		ft_atol(const char *str, long long *result);
t_env	*add_env_to_list(char **envp);

#endif
