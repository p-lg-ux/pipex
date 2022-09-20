/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   content_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgros <pgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 16:18:31 by pgros             #+#    #+#             */
/*   Updated: 2022/09/20 11:47:28 by pgros            ###   ########.fr       */
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
	new->arg = ft_split(new_cmd, ' ');
	if (new->arg != NULL)
		new->cmd_short = ft_strdup((new->arg)[0]);
	new->path = NULL;
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

void	__print_content(t_content *content)
{
	int	i;
	
	ft_printf("cmd : %s\n", content->cmd);
	ft_printf("cmd_short : %s\n", content->cmd_short);
	ft_printf("arg :");
	i = -1;
	while ((content->arg)[++i] != NULL)
		ft_printf(" %s ;", (content->arg)[i]);
	ft_printf("\n");
}

t_content	*__get_content(t_llist *command)
{
	t_content	*ret;
	
	ret = command->content;
	return (ret);
}