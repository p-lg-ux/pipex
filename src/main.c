/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgros <pgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 15:02:11 by pgros             #+#    #+#             */
/*   Updated: 2022/09/09 15:59:54 by pgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int main(int argc, char **argv, char **envp)
{
	t_parse	*parsing;
	
	(void) envp ;
	parsing = __parse(argc, argv);
	if (parsing == NULL)
		return (ft_printf("malloc failed\n"), -1);
	//TODO : check in and out files (existence and/or permission) + open fds
	
	__print_parse(parsing);
	__check_files_permissions(parsing);
	// __execute(parsing, envp);
	__free_parse(parsing);
	return (0);
}