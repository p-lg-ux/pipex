/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_it.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgros <pgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 17:46:29 by pgros             #+#    #+#             */
/*   Updated: 2022/09/21 21:23:33 by pgros            ###   ########.fr       */
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
		content = __get_content(command);
		content_next = __get_content(command->next);
		ret = pipe(content->fds_out);
		if (ret == -1)
			perror("pipe");
		content_next->fds_in[0] = content->fds_out[0];
		content_next->fds_in[1] = content->fds_out[1];
	}
}