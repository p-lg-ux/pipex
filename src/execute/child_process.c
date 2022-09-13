/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgros <pgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 13:58:51 by pgros             #+#    #+#             */
/*   Updated: 2022/09/13 18:38:24 by pgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

//TODO: function __get_paths_list(t_list *command, char **envp)
// Must deal with :
// - the case where the path of the bin is already given instead 
// of just the command.
// - the case where there is no environment (envp = NULL)
// Must return a str_tab like {"/usr/bin/ls", "/bin/ls", NULL}

char	*__find_command_path(t_list *command, char **envp)
{
	char	*path;
	char	**paths_list;
	int		i;
	int		ret;

	path = NULL;
	paths_list = get_paths_list(command, envp);
	if (paths_list != NULL)
	{
		i = 0;
		while (paths_list[i] != NULL)
		{
			ret = access(paths_list[i]);
			if (ret == 0)
			{
				path = paths_list[i];
				break ;
			}
			i++;
		}	
	}
	//TODO: free paths_list
	//TODO: fix the case where NULL must be returned
	(__get_content(command))->path = ft_strdup(path);
	return (path);
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
	perror("");
	exit(EXIT_FAILURE);
}
