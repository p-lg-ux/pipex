/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   content_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgros <pgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 16:18:31 by pgros             #+#    #+#             */
/*   Updated: 2022/09/28 16:17:10 by pgros            ###   ########.fr       */
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

int	__fill_newcontent(t_content *new, char *cmd)
{
	int	ret;

	new->cmd = ft_strdup(cmd);
	if (new->cmd == NULL)
		return (perror("malloc"), __free_content(new), -1);
	new->arg = ft_split(new->cmd, ' ');
	if (new->arg == NULL)
		return (perror("malloc"), __free_content(new), -1);
	if ((new->arg)[0] != NULL)
		new->cmd_short = ft_strdup((new->arg)[0]);
	else
		new->cmd_short = ft_strdup(new->cmd);
	if (new->cmd_short == NULL)
		return (perror("malloc"), __free_content(new), -1);
	ret = __set_path(new, new->cmd_short);
	if (ret < 0)
		return (__free_content(new), -1);
	__set_fds(new);
	return (0);
}

t_content	*__newcontent(char *cmd)
{
	t_content	*new;
	int			ret;

	new = ft_calloc(1, sizeof(t_content));
	if (new == NULL)
		return (perror("malloc"), NULL);
	ret = __fill_newcontent(new, cmd);
	if (ret < 0)
		return (NULL);
	return (new);
}

t_content	*__get_content(t_llist *command)
{
	t_content	*ret;

	if (command  == NULL)
		return (NULL);
	ret = command->content;
	return (ret);
}
