/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_fds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgros <pgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 16:47:09 by pgros             #+#    #+#             */
/*   Updated: 2022/09/20 11:49:14 by pgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

int	__open_fds(t_parse *parsing)
{
	int		fds_files[2];
	t_llist	*command;

	fds_files[0] = open(parsing->infile, O_RDONLY);
	fds_files[1] = open(parsing->outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fds_files[0] < 0 || fds_files[1] < 0)
		return(perror(), -1);
	command = parsing->commands;
	((t_content *) command)->fds_in = fds_files;
	command = ft_llstlast(parsing->commands);
	((t_content *) command)->fds_out = fds_files;
	return (0);
}