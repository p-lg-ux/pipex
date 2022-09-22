/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_fds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgros <pgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 16:47:09 by pgros             #+#    #+#             */
/*   Updated: 2022/09/22 18:00:25 by pgros            ###   ########.fr       */
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
		__ultimate_exit(command, "open");
	content->fds_in[0] = fd;
}

void	__open_outfile(t_llist *command)
{
	int			fd;
	t_content	*content;

	content = __get_content(command);
	fd = open(content->parsing->outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
		__ultimate_exit(command, "open");
	content->fds_out[1] = fd;
}

void	__open_files(t_llist *command)
{
	if (command->previous == NULL)
		__open_infile(command);
	if (command->next == NULL)
		__open_outfile(command);
}

// int	__open_fds(t_parse *parsing)
// {
// 	int		fds_files[2];
// 	t_llist	*command;

// 	fds_files[0] = open(parsing->infile, O_RDONLY);
// 	fds_files[1] = open(parsing->outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
// 	if (fds_files[0] < 0 || fds_files[1] < 0)
// 		return(perror(), -1);
// 	command = parsing->commands;
// 	((t_content *) command)->fds_in = fds_files;
// 	command = ft_llstlast(parsing->commands);
// 	((t_content *) command)->fds_out = fds_files;
// 	return (0);
// }