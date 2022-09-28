/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgros <pgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 15:10:49 by pgros             #+#    #+#             */
/*   Updated: 2022/09/28 19:31:12 by pgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

int	__fill_commands_llist(t_parse *parsing, int argc, char **argv)
{
	t_llist		*node;
	t_content	*content;
	int			i;
	
	i = 1;
	while (++i < argc - 1)
	{
		content = __newcontent(argv[i]);
		if (content == NULL)
			return (-1);
		content->parsing = parsing;
		node = ft_llstnew(content);
		if (node == NULL)
			return (perror("malloc"), __free_content(content), -1);
		ft_llstadd_back(&(parsing->commands), node);
	}
	return (0);
}

t_parse	*__parse(int argc, char **argv)
{
	t_parse	*parsing;
	int		ret;

	parsing = ft_calloc(1, sizeof(t_parse));
	if (parsing == NULL)
		return (perror("malloc"), NULL);
	parsing->infile = ft_strdup(argv[1]);
	if (parsing->infile == NULL)
		return (perror("malloc"), __free_parse(parsing), NULL);
	parsing->outfile = ft_strdup(argv[argc - 1]);
	if (parsing->outfile == NULL)
		return (perror("malloc"), __free_parse(parsing), NULL);
	ret = __fill_commands_llist(parsing, argc, argv);
	if (ret < 0)
		return (__free_parse(parsing), NULL);
	return (parsing);
}
