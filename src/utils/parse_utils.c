/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgros <pgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 17:04:30 by pgros             #+#    #+#             */
/*   Updated: 2022/09/07 17:56:44 by pgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

void	__free_parse(t_parse *parsing)
{
	if (parsing == NULL)
		return ;
	if (parsing->infile != NULL)
		free(parsing->infile);
	if (parsing->outfile != NULL)
		free(parsing->outfile);
	ft_lstclear(&(parsing->commands), &__free_content);
	free(parsing);
}

void	__print_parse(t_parse *parsing)
{
	ft_printf("--------------------\nPARSING\n");
	if (parsing == NULL)
		ft_printf("(null)\n");
	else
	{
		ft_printf("infile : %s\n", parsing->infile);
		__print_lst(parsing->commands);
		ft_printf("outfile : %s\n", parsing->outfile);
	}
	ft_printf("--------------------\n");
}