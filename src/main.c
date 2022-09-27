/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgros <pgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 15:02:11 by pgros             #+#    #+#             */
/*   Updated: 2022/09/27 16:48:28 by pgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

// TODO 3 : bien proteger tous les mallocs avec ultimate_exit, notamment ceux des fonctions de la libft
// TODO : faire le bonus heredoc
// TODO 5 : faire tester la version actuelle a Roland
// TODO : Gerer le cas de lexecution d'un non binaire (ex : ./cat dans lequel il y a ls) et eviter l'erreur execve
// TODO 1 : ./pipex "" "" "" "" => segfault
// TODO 2 : ./pipex a b c d => erreur de valgrind : fd (pipe) restent open
// TODO 4 : normer le code

int main(int argc, char **argv, char **envp)
{
	t_parse	*parsing;
	// char	**str_tab;
	
	if (argc < 5)
	{
		ft_putstr_fd("Not enough arguments\n", STDERR_FILENO);
		return (-1);
	}
	parsing = __parse(argc, argv);
	if (parsing == NULL)
		return (ft_printf("malloc failed\n"), -1);
	
	// __print_parse(parsing);
	// __check_files_permissions(parsing);
	// str_tab = __get_path_var_tab(parsing->commands->next, envp);
	// printf("\npaths_list :\n");
	// __print_strtab(str_tab);
	__execute(parsing, envp);
	__free_parse(parsing);
	// __free_strtab(str_tab);
	return (0);
}