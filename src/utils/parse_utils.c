/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgros <pgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 17:04:30 by pgros             #+#    #+#             */
/*   Updated: 2022/09/23 16:05:24 by pgros            ###   ########.fr       */
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
	ft_llstclear(&(parsing->commands), &__free_content);
	free(parsing);
}
