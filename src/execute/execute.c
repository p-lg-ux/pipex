/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgros <pgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 13:37:13 by pgros             #+#    #+#             */
/*   Updated: 2022/09/09 17:46:31 by pgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

void	__child_process(t_list *command, char **envp)
{
	
}

void	__fork_process(t_list *command, char **envp)
{
	int	child;

	child = fork();
	if (child < -1)
	{
		perror();
		exit(EXIT_FAILURE);
	}
	if (child == 0)
		__child_process(command, envp);
}

void	__execute(t_parse *parsing, char **envp)
{
	t_list	*commands;

	__open_fds(parsing);
	command = parsing->commands;
	while (command != NULL)
	{
		__fork_process(command, envp);
		command = commands->next;
	}
}
