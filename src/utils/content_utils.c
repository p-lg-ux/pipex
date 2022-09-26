/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   content_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgros <pgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 16:18:31 by pgros             #+#    #+#             */
/*   Updated: 2022/09/26 16:42:20 by pgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

void	__set_path(t_content *content, char *cmd_short)
{
	if (content == NULL || cmd_short == NULL)
		return ;
	content->path = NULL;
	if (ft_strncmp(cmd_short, "/", 1) == 0)
		content->path = ft_strdup(cmd_short);
	if (ft_strncmp(cmd_short, "./", 2) == 0)
		content->path = ft_strdup(cmd_short);
	if (ft_strncmp(cmd_short, "../", 3) == 0)
		content->path = ft_strdup(cmd_short);
	if (ft_strncmp(cmd_short, "~/", 2) == 0)
		content->path = ft_strdup(cmd_short);
	return ;
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
	new->arg = ft_split(new_cmd, ' ');
	if (new->arg != NULL)
	{
		if ((new->arg)[0] != NULL)
			new->cmd_short = ft_strdup((new->arg)[0]);
		else
			new->cmd_short = ft_strdup(new->cmd);
	}
	__set_path(new, new->cmd_short);
	__set_fds(new);
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
	if (content->path != NULL)
		free(content->path);
	if (content->cmd_short != NULL)
		free(content->cmd_short);
	__free_strtab(content->arg);
	free(content);
}

t_content	*__get_content(t_llist *command)
{
	t_content	*ret;

	ret = command->content;
	return (ret);
}
