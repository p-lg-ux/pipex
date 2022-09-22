/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgros <pgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 13:37:13 by pgros             #+#    #+#             */
/*   Updated: 2022/09/22 16:53:06 by pgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

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
		perror("fork");
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
