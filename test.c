/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgros <pgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 17:28:45 by pgros             #+#    #+#             */
/*   Updated: 2022/09/15 15:44:53 by pgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>
#include "./lib42/lib42.h"

void	__free_strtab(char **tab)
{
	int	i;
	
	if (tab == NULL)
		return ;
	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	**__get_path_var_str(char **envp)
{
	char 		*path_str;
	char		**path_tab;
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
	if (path_str == NULL)
			path_str = "";
	path_str = ft_strtrim(path_str, "PATH=");
	path_tab = ft_split(path_str, ':');
	free(path_str);
	return (path_tab);
}

int main(int argc, char **argv, char **envp)
{
	char	**tab;
	int		i;
	
	(void) argv;
	tab = __get_path_var_str(envp);
	printf("tab :\n");
	i = 0;
	while (tab[i] != NULL)
	{
		printf("\"%s\"\n", tab[i]);
		i++;
	}
	__free_strtab(tab);
	return (argc- argc);
}