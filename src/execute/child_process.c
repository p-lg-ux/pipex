/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgros <pgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 13:58:51 by pgros             #+#    #+#             */
/*   Updated: 2022/09/20 17:11:18 by pgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

void	__duplicate_fds(t_llist *command)
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

void	__child_process(t_llist *command, char **envp)
{
	char		*path;
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
