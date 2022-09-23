/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ultimate_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgros <pgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:00:34 by pgros             #+#    #+#             */
/*   Updated: 2022/09/23 13:33:44 by pgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

/**
 * @brief Closes the pipe in input of command
 * 
 * @param command 
 */
void	__close_fds_in(t_llist *command)
{
	int	fd;

	fd = (__get_content(command))->fds_in[0];
	if (fd != -1)
	{
		close(fd);
		(__get_content(command))->fds_in[0] = -1;
	}
	fd = (__get_content(command))->fds_in[1];
	if (fd != -1)
	{
		close(fd);
		(__get_content(command))->fds_in[1] = -1;
	}
}

/**
 * @brief Closes the pipe in output of command
 * 
 * @param command 
 */
void	__close_fds_out(t_llist *command)
{
	int	fd;

	fd = (__get_content(command))->fds_out[0];
	if (fd != -1)
	{
		close(fd);
		(__get_content(command))->fds_out[0] = -1;
	}
	fd = (__get_content(command))->fds_out[1];
	if (fd != -1)
	{
		close(fd);
		(__get_content(command))->fds_out[1] = -1;
	}
}

/**
 * @brief Closes all the pipes of the chained list.
 * 
 * @param command any node of the chained list.
 */
void	__close_all_fds(t_llist *command)
{
	while (command->previous != NULL)
		command = command->previous;
	while (command != NULL)
	{
		__close_fds_in(command);
		__close_fds_out(command);
	}
}

void	__ultimate_exit(t_llist *command, char *message)
{
	perror(message);
	__free_parse((__get_content(command))->parsing);
	exit(EXIT_FAILURE);
}