/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgros <pgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 17:36:43 by pgros             #+#    #+#             */
/*   Updated: 2022/09/30 16:21:12 by pgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

void	__command_error(t_llist *command, char **paths_list)
{
	t_content	*content;
	char		*message;

	__free_strtab(paths_list);
	content = __get_content(command);
	message = ft_strjoin(content->cmd_short, ": command not found\n");
	ft_putstr_fd(message, STDERR_FILENO);
	free(message);
	__close_all_fds(command);
	__free_parse((__get_content(command))->parsing);
	exit(EXIT_FAILURE);
}

void	__check_all_paths(t_llist *command, char **envp)
{
	char		**paths_list;
	int			i;

	paths_list = __get_paths_list(command, envp);
	if (paths_list == NULL)
		__ultimate_exit(command, NULL, CLOSE_FDS);
	i = -1;
	while (paths_list[++i] != NULL)
	{
		if (access(paths_list[i], X_OK) == 0)
			break ;
	}
	if (paths_list[i] == NULL || (__get_content(command)->cmd_short)[0] == '\0')
		__command_error(command, paths_list);
	else
	{
		__get_content(command)->path = ft_strdup(paths_list[i]);
		if (__get_content(command)->path == NULL)
		{
			__free_strtab(paths_list);
			__ultimate_exit(command, "malloc", CLOSE_FDS);
		}
	}
	__free_strtab(paths_list);
}

void	__find_command_path(t_llist *command, char **envp)
{
	t_content	*content;
	int			ret;

	content = __get_content(command);
	if (content->path != NULL)
	{
		ret = access(content->path, X_OK);
		if (ret < 0)
			__ultimate_exit(command, content->path, CLOSE_FDS);
	}
	else
		__check_all_paths(command, envp);
}
