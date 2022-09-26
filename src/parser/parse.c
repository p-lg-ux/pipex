/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgros <pgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 15:10:49 by pgros             #+#    #+#             */
/*   Updated: 2022/09/26 15:15:53 by pgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

t_parse	*__parse(int argc, char **argv)
{
	t_parse		*parsing;
	t_llist		*node;
	t_content	*content;
	int			i;

	parsing = ft_calloc(1, sizeof(t_parse));
	if (parsing == NULL)
		return (NULL);
	i = 1;
	while (++i < argc - 1)
	{
		content = __newcontent(argv[i]);
		if (content == NULL)
			return (__free_parse(parsing), NULL);
		content->parsing = parsing;
		node = ft_llstnew(content);
		if (node == NULL)
			return (__free_parse(parsing), __free_content(content), NULL);
		ft_llstadd_back(&(parsing->commands), node);
	}
	parsing->infile = ft_strdup(argv[1]);
	parsing->outfile = ft_strdup(argv[argc - 1]);
	if (parsing->infile == NULL || parsing->outfile == NULL)
		return (__free_parse(parsing), NULL);
	return (parsing);
}
