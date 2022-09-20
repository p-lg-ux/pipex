/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_it.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgros <pgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 17:46:29 by pgros             #+#    #+#             */
/*   Updated: 2022/09/20 17:50:24 by pgros            ###   ########.fr       */
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
/*
	if (command->previous == NULL)
	{
		__open_infile(command, __get_content(command)->parsing->infile);
		__pipe_fds(command);
	}
	else if (command->next == NULL)
		__open_outfile(command, __get_content(command)->parsing->outfile);
	else
		__pipe_fds(command);*/
	if (command->next != NULL)
	{
		fds = (__get_content(command))->fds_out;
		ret = pipe(fds);
		if (ret == -1)
			perror("pipe")
		((__get_content(command->next))->fds_in)[0] = fds[0];
		((__get_content(command->next))->fds_in)[1] = fds[1];
	}
}