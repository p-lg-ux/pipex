/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgros <pgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 13:58:51 by pgros             #+#    #+#             */
/*   Updated: 2022/09/14 18:24:19 by pgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

//TODO: function __get_path_var_str(char **envp)
char	*__get_path_var_str(char **envp)
{
	char 		*path_str;
	int			i;
	
	i = 0;
	path_str = NULL;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path_str = envp[i];
			break ;
		}
		i++;
	}
	if (path_str != NULL)
		path_str = ft_strtrim(path_str, "PATH=");
	return (path_str);
}

//TODO: function __get_path_var_tab(char **envp)
// Extracts all paths possible from the environment variable PATH and returns
// them in a strtab
char	**__get_path_var_tab(t_list *command, char **envp)
{
	char	**path_var_tab;
	char	*path_var_str;
	
	if (envp = NULL)
		return (NULL);
	path_var_str = __get_path_var_str(envp);
	
	return (path_var_tab);
}

//TODO: function __get_paths_list(t_list *command, char **envp)
// Must deal with :
// - the case where the path of the bin is already given instead 
// of just the command.
// - the case where there is no environment (envp = NULL)
// Must return a str_tab like {"/usr/bin/ls", "/bin/ls", NULL}
char	**__get_paths_list(t_list *command, char **envp)
{
	char	**str_tab;
	char	**path_var;
	int		len;
	
	path_var = __get_path_var_tab(command, envp);
}

char	*__find_command_path(t_list *command, char **envp)
{
	char	**paths_list;
	int		i;
	int		ret;

	paths_list = get_paths_list(command, envp);
	if (paths_list == NULL)
		return (NULL);
	i = 0;
	while (paths_list[i] != NULL)
	{
		ret = access(paths_list[i]);
		if (ret == 0)
			break ;
		i++;
	}
	if (paths_list[i] != NULL)
		(__get_content(command))->path = ft_strdup(path);	
	__free_strtab(paths_list);
	return ((__get_content(command))->path);
}

void	__dupicate_fds(t_list *command)
{
	t_content	*content;
	int			ret;

	content = __get_content(command);
	close(content->fds_in[1]);
	close(content->fds_out[0]);
	ret = dup2(content->fds_in[0], STDIN_FILENO);
	if (ret < 0)
		perror("dup2");
	close(content->fds_in[0]);
	ret = dup2(content->fds_out[1], STDOUT_FILENO);
	if (ret < 0)
		perror("dup2");
	close(content->fds_out[1]);
}

void	__child_process(t_list *command, char **envp)
{
	char		*path;
	int			i;
	t_content	*content;

	__duplicate_fds(command);
	path = __find_command_path(command, envp);
	content = __get_content(command);
	if (path == NULL)
	{	
		ft_putstr_fd(content->cmd_short, STDERR_FILENO);
		ft_putstr_fd(": command not found.\n", STDERR_FILENO);
	}
	execve(path, content->arg, envp);
	perror("execve");
	exit(EXIT_FAILURE);
}
