/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgros <pgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 17:28:45 by pgros             #+#    #+#             */
/*   Updated: 2022/09/14 17:44:31 by pgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>
#include "./lib42/lib42.h"

char	*__get_path_var_str(char **envp)
{
	char 		*path_str;
	int			i;
	
	i = 0;
	path_str = NULL;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path_str = envp[i];
			break ;
		}
		i++;
	}
	if (path_str != NULL)
		path_str = ft_strtrim(path_str, "PATH=");
	return (path_str);
}

int main(int argc, char **argv, char **envp)
{
	char *path_str;

	(void) argv;
	path_str = NULL;
	if (envp != NULL)
		path_str = __get_path_var_str(envp);
	printf("path : \"%s\"\n", path_str);
	return (argc- argc);
}