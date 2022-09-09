/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   content_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgros <pgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 16:18:31 by pgros             #+#    #+#             */
/*   Updated: 2022/09/09 17:11:26 by pgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

t_content	*__newcontent(char *cmd)
{
	t_content	*new;
	char		*new_cmd;
	
	new_cmd = ft_strdup(cmd);
	if (new_cmd == NULL)
		return (NULL);
	new = ft_calloc(1, sizeof(t_content));
	if (new == NULL)
		return (NULL);
	new->cmd = new_cmd;
	return (new);
}

void	__free_content(void *c)
{
	t_content	*content;
	
	content = c;
	if (content == NULL)
		return ;
	if (content->cmd != NULL)
		free(content->cmd);
	free(content);
}

void	__print_content(t_content *content)
{
	ft_printf("cmd : %s (%i -> %i)\n", content->cmd,
		(content->fds_in)[0], (content->fds_in)[1]);
}