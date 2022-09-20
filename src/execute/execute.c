/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgros <pgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 13:37:13 by pgros             #+#    #+#             */
/*   Updated: 2022/09/20 11:47:28 by pgros            ###   ########.fr       */
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
	int	fds[2];
	int	ret;

	fds = (__get_content(command))->fds_out;
	ret = pipe(fds);
	if (ret == -1)
		perror("pipe")
	((__get_content(command->next))->fds_in)[0] = fds[0];
	((__get_content(command->next))->fds_in)[1] = fds[1];
}

/**
 * @brief Opens the output pipe in the parent, and forks the process
 * 
 * @param command Current command. Node of the chained list of commands.
 * @param envp Dictionnary of environment variables.
 */
void	__fork_process(t_llist *command, char **envp)
{
	int	child;
	
	if (command->next != NULL)
		__pipe_it(command);
	child = fork();
	if (child < -1)
		perror("fork");
	if (child == 0)
		__child_process(command, envp);
}

/**
 * @brief Closes the pipe in input of command
 * 
 * @param command 
 */
void	__close_fds_in(t_llist *command)
{
	close((__get_content(command))->fds_in[0]);
	close((__get_content(command))->fds_in[1]);
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
	t_llist	*commands;

	__open_fds(parsing);
	command = parsing->commands;
	while (command != NULL)
	{
		__fork_process(command, envp);
		if (command != parsing->commands)
			__close_fds_in(command);
		command = commands->next;
	}
}
