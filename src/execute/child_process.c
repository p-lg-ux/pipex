/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgros <pgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 13:58:51 by pgros             #+#    #+#             */
/*   Updated: 2022/09/28 18:50:34 by pgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"
/*
void	__duplicate_fds(t_llist *command)
{
	t_content	*content;
	int			ret;

	content = __get_content(command);
	// if (content->fds_in[1] != -1)
	// 	close(content->fds_in[1]);
	// if (content->fds_out[0] != -1)
	// 	close(content->fds_out[0]);
	// content->fds_in[1] = -1;
	// content->fds_out[0] = -1;
	ret = dup2(content->fds_in[0], STDIN_FILENO);
	if (ret < 0)
		__ultimate_exit(command, "dup2", CLOSE_FDS);
	// close(content->fds_in[0]);
	ret = dup2(content->fds_out[1], STDOUT_FILENO);
	if (ret < 0)
		__ultimate_exit(command, "dup2", CLOSE_FDS);
	// close(content->fds_out[1]);
	__close_fds_in(command);
	__close_fds_out(command);
}
*/
void	__duplicate_fds(t_llist *command)
{
	t_content	*content;
	int			ret;

	content = __get_content(command);
	ret = dup2(content->fds_in[0], STDIN_FILENO);
	if (ret < 0)
		__ultimate_exit(command, "dup2", CLOSE_FDS);
	ret = dup2(content->fds_out[1], STDOUT_FILENO);
	if (ret < 0)
		__ultimate_exit(command, "dup2", CLOSE_FDS);
	__close_fds_in(command);
	__close_fds_out(command);
}

void	__child_process(t_llist *command, char **envp)
{
	t_content	*content;

	__open_files(command);
	__find_command_path(command, envp);
	__duplicate_fds(command);
	content = __get_content(command);
	execve(content->path, content->arg, envp);
	__ultimate_exit(command, "execve", CLOSE_FDS);
}
