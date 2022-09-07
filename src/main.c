/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgros <pgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 15:02:11 by pgros             #+#    #+#             */
/*   Updated: 2022/09/07 20:25:33 by pgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int main(int argc, char **argv, char **envp)
{
	t_parse	*parsing;
	
	parsing = __parse(argc, argv);
	//TODO : case if (parsing == NULL)
	__print_parse(parsing);
	__execute(parsing, envp);
	__free_parse(parsing);
	return (0);
}