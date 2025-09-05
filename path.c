/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 15:50:18 by mabaghda          #+#    #+#             */
/*   Updated: 2025/09/05 18:05:21 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*find_path(t_env **env) {
  t_env *tmp;

  tmp = *env;
  while (tmp) {
    if (ft_strcmp(tmp->key, "PATH") == 0)
      return (tmp);
    tmp = tmp->next;
  }
  return (NULL);
}

char	*split_path(t_env **env, char *cmd) {
  int i;
  t_env *path;
  char **splitted_path;
  char *idk;
  char *tmp;

  path = find_path(env);
  if (!path)
    return (NULL);
  splitted_path = ft_split(path->value, ':');
  i = 0;
  if (ft_strchr(cmd, '/')) {
    if (access(cmd, X_OK) == 0)
      return (cmd);
  }
  while (splitted_path[i]) {
    idk = ft_strjoin(splitted_path[i], "/");
    tmp = ft_strjoin(idk, cmd);
    free(idk);
    idk = tmp;
    if (access(idk, X_OK) == 0) {
      free_array(splitted_path);
      return (idk);
    }
    free(idk);
    i++;
  }
  free_array(splitted_path);
  return (NULL);
}

// char	**envp_from_list(t_env *env) {
//   int len;
//   char **envp;
//   t_env *tmp;
//   int i;
//   char *str;

//   len = 0;
//   tmp = env;
//   while (tmp) {
//     len++;
//     tmp = tmp->next;
//   }
//   envp = malloc(sizeof(char *) * (len + 1));
//   if (!envp)
//     return (NULL);
//   i = 0;
//   tmp = env;
//   while (tmp) {
//     str = ft_strjoin(tmp->key, "=");
//     envp[i] = ft_strjoin(str, tmp->value);
//     free(str);
//     i++;
//     tmp = tmp->next;
//   }
//   envp[i] = NULL;
//   return (envp);
// }

void	free_envp(char **envp) {
  int i;

  i = 0;
  if (!envp)
    return ;
  while (envp[i])
    free(envp[i++]);
  free(envp);
}

void	child_process_execution(t_env **env, char **cmd) {
  char *path;
  char **envp;

  signal(SIGINT, SIG_DFL);
  signal(SIGQUIT, SIG_DFL);
  change_shlvl_value(env, cmd);
  envp = env_to_envp(*env);
  if (!envp)
    exit(1);
  path = split_path(env, cmd[0]);
  if (!path) {
    free_envp(envp);
    exit(127);
  }
  if (!cmd[0] || is_builtin_cmd(cmd[0])) {
    free(path);
    free_envp(envp);
    printf("%s %s: command not found\n", cmd[0], cmd[1]);
    exit(126);
  }
  if (execve(path, cmd, envp) == -1) {
    perror(cmd[0]);
    free(path);
    free_envp(envp);
    exit(126);
  }
}

void	parent_process_handling(pid_t pid, int *status, char **cmd) {
  int sig;

  signal(SIGINT, SIG_IGN);
  signal(SIGQUIT, SIG_IGN);
  if (waitpid(pid, status, 0) == -1)
    perror("waitpid");
  signal(SIGINT, sigint_handler);
  signal(SIGQUIT, sigquit_handler);
  if (WIFEXITED(*status))
    g_exit_status = WEXITSTATUS(*status);
  else if (WIFSIGNALED(*status)) {
    sig = WTERMSIG(*status);
    g_exit_status = 128 + sig;
    if (sig == SIGINT)
      write(1, "\n", 1);
    else if (sig == SIGQUIT)
      write(1, "Quit: 3\n", 8);
  }
  if (g_exit_status == 127)
    printf("%s: command not found\n", cmd[0]);
}

void	execute_else(t_env **env, char **cmd) {
  pid_t pid;
  int status;

  pid = fork();
  if (pid < 0) {
    perror("fork");
    return ;
  }
  if (pid == 0)
    child_process_execution(env, cmd);
  else
    parent_process_handling(pid, &status, cmd);
}
