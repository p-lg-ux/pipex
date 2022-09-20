/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgros <pgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 17:04:30 by pgros             #+#    #+#             */
/*   Updated: 2022/09/20 11:51:15 by pgros            ###   ########.fr       */
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

void	__print_parse(t_parse *parsing)
{
	ft_printf("--------------------\nPARSING\n");
	if (parsing == NULL)
		ft_printf("(null)\n");
	else
	{
		ft_printf("infile : %s\n", parsing->infile);
		__print_llst(parsing->commands);
		ft_printf("outfile : %s\n", parsing->outfile);
	}
	ft_printf("--------------------\n");
}

/**
 * @brief Checks that the infile exists and is readable and that the outfile is
 * is writable if it exists. Writes error messages on stdrror.
 *
 * @param parsing : struct s_parse, resulting from the parsing of pipex
 * arguments (see pipex.h).
 * @return int : 0 if all checks are ok, -1 in the other case.
 */
int	__check_files_permissions(t_parse *parsing)
{
	int	access_ret;
	int ret;

	ret = 0;
	access_ret = access(parsing->infile, R_OK);
	if (access_ret == -1)
	{
		perror(parsing->infile);
		ret = -1;
	}
	access_ret = access(parsing->outfile, F_OK);
	if (access_ret == 0)
	{
		access_ret = access(parsing->outfile, W_OK);
		if (access_ret == -1)
		{
			perror(parsing->outfile);
			ret = -1;
		}
	}
	return (ret);
}
