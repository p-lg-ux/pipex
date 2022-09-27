/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_fds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgros <pgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 16:47:09 by pgros             #+#    #+#             */
/*   Updated: 2022/09/27 16:20:48 by pgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

void	__open_infile(t_llist *command)
{
	int			fd;
	t_content	*content;

	content = __get_content(command);
	fd = open(content->parsing->infile, O_RDONLY);
	if (fd < 0)
		__ultimate_exit(command, content->parsing->infile, CLOSE_FDS);
	content->fds_in[0] = fd;
}

void	__open_outfile(t_llist *command)
{
	int			fd;
	t_content	*content;

	content = __get_content(command);
	fd = open(content->parsing->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		__ultimate_exit(command, content->parsing->outfile, CLOSE_FDS);
	content->fds_out[1] = fd;
}

void	__open_files(t_llist *command)
{
	if (command->previous == NULL)
		__open_infile(command);
	if (command->next == NULL)
		__open_outfile(command);
}
