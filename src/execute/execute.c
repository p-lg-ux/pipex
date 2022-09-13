/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgros <pgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 13:37:13 by pgros             #+#    #+#             */
/*   Updated: 2022/09/13 13:59:12 by pgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

/**
 * @brief Opens the pipe that will receive the output of command. Sets this
 * pipe as the input of the next command.
 * 
 * @param command Current command. Node of the chained list of commands.
 */
void	__pipe_it(t_list *command)
{
	int	fds[2];
	int	ret;

	fds = (__get_content(command))->fds_out;
	ret = pipe(fds);
	if (ret == -1)
		perror("pipe")
	(__get_content(command->next))->fds_in = fds;
}

/**
 * @brief Opens the output pipe in the parent, and forks the process
 * 
 * @param command Current command. Node of the chained list of commands.
 * @param envp Dictionnary of environment variables.
 */
void	__fork_process(t_list *command, char **envp)
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
void	__close_fds_in(t_list *command)
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
	t_list	*commands;

	__open_fds(parsing);
	command = parsing->commands;
	while (command != NULL)
	{
		__fork_process(command, envp);
		wait();
		if (command != parsing->commands)
			__close_fds_in(command);
		command = commands->next;
	}
}
