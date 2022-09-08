/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgros <pgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 13:37:13 by pgros             #+#    #+#             */
/*   Updated: 2022/09/08 16:17:09 by pgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

void	__execute(t_parse *parsing, char **envp)
{
	// int	pfd[2];
	t_list	*commands;

	// if (pipe(pfd) == -1)
	// {
	// 	ft_printf("pipe failed\n");
	// 	return ;
	// }
	commands = parsing->commands;
	while (commands != NULL)
	{
		
		commands = commands->next;
	}
}
