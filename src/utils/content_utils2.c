/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   content_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgros <pgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 13:54:49 by pgros             #+#    #+#             */
/*   Updated: 2022/09/30 13:55:17 by pgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

int	__set_path(t_content *content, char *cmd_short)
{
	if (content == NULL || cmd_short == NULL)
		return (-1);
	content->path = NULL;
	if (ft_strchr(cmd_short, '/') != NULL)
	{
		content->path = ft_strdup(cmd_short);
		if (content->path == NULL)
			return (perror("malloc"), -1);
	}
	return (0);
}

void	__set_fds(t_content *content)
{
	if (content == NULL)
		return ;
	(content->fds_in)[0] = -1;
	(content->fds_in)[1] = -1;
	(content->fds_out)[0] = -1;
	(content->fds_out)[1] = -1;
}