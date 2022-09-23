/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgros <pgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:02:59 by pgros             #+#    #+#             */
/*   Updated: 2022/09/23 16:05:49 by pgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

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
	ft_printf("path : %s\n", content->path);
	ft_printf("fds_in : %i -> %i\n", (content->fds_in)[1], (content->fds_in)[0]);
	ft_printf("fds_out : %i -> %i\n", (content->fds_out)[1],
		(content->fds_out)[0]);
}

void	__print_llst(t_llist *llst)
{
	t_content	*content;

	while (llst != NULL)
	{
		content = llst->content;
		__print_content(content);
		ft_printf("\n");
		llst = llst->next;
	}
}

void	__print_parse(t_parse *parsing)
{
	ft_printf("--------------------\nPARSING\n");
	if (parsing == NULL)
		ft_printf("(null)\n");
	else
	{
		ft_printf("infile : %s\n\n", parsing->infile);
		__print_llst(parsing->commands);
		ft_printf("outfile : %s\n", parsing->outfile);
	}
	ft_printf("--------------------\n");
}

void	__print_strtab(char **tab)
{
	int	i;

	if (tab == NULL)
		return ;
	i = 0;
	while (tab[i] != NULL)
	{
		printf("%s\n", tab[i]);
		i++;
	}
}
