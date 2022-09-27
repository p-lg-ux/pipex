/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgros <pgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 13:37:13 by pgros             #+#    #+#             */
/*   Updated: 2022/09/27 15:20:05 by pgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

/**
 * @brief Opens the pipe that will receive the output of command. Sets this
 * pipe as the input of the next command.
 * 
 * @param command Current command. Node of the chained list of commands.
 */
void	__pipe_it(t_llist *command)
{
	int			ret;
	t_content	*content;
	t_content	*content_next;

	if (command->next != NULL)
	{
		content = __get_content(command);
		content_next = __get_content(command->next);
		ret = pipe(content->fds_out);
		if (ret == -1)
			__ultimate_exit(command, "pipe", CLOSE_FDS);
		content_next->fds_in[0] = content->fds_out[0];
		content_next->fds_in[1] = content->fds_out[1];
	}
}

/**
 * @brief Opens the output pipe in the parent, and forks the process
 * 
 * @param command Current command. Node of the chained list of commands.
 * @param envp Dictionnary of environment variables.
 */
void	__fork_process(t_llist *command, char **envp)
{
	int	child_pid;

	child_pid = fork();
	if (child_pid < -1)
		__ultimate_exit(command, "fork", CLOSE_FDS);
	if (child_pid == 0)
		__child_process(command, envp);
}

/**
 * @brief Opens the fd for the infile and the outfile and executes all
 * commands in the chained list.
 * 
 * @param parsing 
 * @param envp 
 */
void	__execute(t_parse *parsing, char **envp)
{
	t_llist	*command;
	int		ret;

	command = parsing->commands;
	while (command != NULL)
	{
		__pipe_it(command);
		__fork_process(command, envp);
		__close_fds_in(command);
		if (command->next == NULL)
			__close_fds_out(command);
		command = command->next;
	}
	ret = 0;
	while (ret != -1 || errno != ECHILD)
		ret = wait(NULL);
}
