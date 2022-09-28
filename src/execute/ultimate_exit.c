/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ultimate_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgros <pgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:00:34 by pgros             #+#    #+#             */
/*   Updated: 2022/09/28 18:33:48 by pgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

/**
 * @brief Closes the pipe in input of command
 * 
 * @param command a node of the chained list.
 */
void	__close_fds_in(t_llist *command)
{
	int	fd;
	int	ret;

	fd = (__get_content(command))->fds_in[0];
	if (fd != -1)
	{
		ret = close(fd);
		if (ret < 0)
			__ultimate_exit(command, "close", DONT_CLOSE_FDS);
		(__get_content(command))->fds_in[0] = -1;
		if (command->previous != NULL)
			(__get_content(command->previous))->fds_out[0] = -1;
	}
	fd = (__get_content(command))->fds_in[1];
	if (fd != -1)
	{
		ret = close(fd);
		if (ret < 0)
			__ultimate_exit(command, "close", DONT_CLOSE_FDS);
		(__get_content(command))->fds_in[1] = -1;
		if (command->previous != NULL)
			(__get_content(command->previous))->fds_out[1] = -1;
	}
}

/**
 * @brief Closes the pipe in output of command
 * 
 * @param command a node of the chained list.
 */
void	__close_fds_out(t_llist *command)
{
	int	fd;
	int	ret;

	fd = (__get_content(command))->fds_out[0];
	if (fd != -1)
	{
		ret = close(fd);
		if (ret < 0)
			__ultimate_exit(command, "close", DONT_CLOSE_FDS);
		(__get_content(command))->fds_out[0] = -1;
		if (command->next != NULL)
			(__get_content(command->next))->fds_in[0] = -1;
	}
	fd = (__get_content(command))->fds_out[1];
	if (fd != -1)
	{
		ret = close(fd);
		if (ret < 0)
			__ultimate_exit(command, "close", DONT_CLOSE_FDS);
		(__get_content(command))->fds_out[1] = -1;
		if (command->next != NULL)
			(__get_content(command->next))->fds_out[0] = -1;
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
	__close_fds_in(command);
	while (command != NULL)
	{
		__close_fds_out(command);
		command = command->next;
	}
}

/**
 * @brief Prints the error message, optionaly closes all the open fds of the
 * process, frees all allocated variables and exits the process.
 * 
 * @param command any node of the chained list.
 * @param message the string to be passed to perror.
 * @param do_close_fds CLOSE_FDS (1) if the fds must be closed,
 * DONT_CLOSE_FDS (0) otherwise.
 */
void	__ultimate_exit(t_llist *command, char *message,
			t_do_close do_close_fds)
{
	perror(message);
	if (do_close_fds == CLOSE_FDS)
		__close_all_fds(command);
	__free_parse((__get_content(command))->parsing);
	exit(EXIT_FAILURE);
}
