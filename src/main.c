/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgros <pgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 15:02:11 by pgros             #+#    #+#             */
/*   Updated: 2022/10/03 14:16:23 by pgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

// TODO 5 : bien proteger tous les mallocs avec ultimate_exit, notamment ceux des fonctions de la libft
// TODO 5.2 : checker toutes les protections de mallocs
// TODO 6 : reduire les fonctions trop longues et ajouter les nouvelles fonctions a pipex.h
// ? TODO : faire le bonus heredoc
// TODO 8 : faire tester la version actuelle a Roland
// ? TODO : Gerer le cas de lexecution d'un non binaire (ex : ./cat dans lequel il y a ls) et eviter l'erreur execve
// DONE 1 : ./pipex "" "" "" "" => segfault
// DONE 2 : ./pipex a b c d => erreur de valgrind : fd (pipe) restent open
// TODO 7 : normer le code
// DONE 3 : modifier __set_path de facon a ce qu'un path soit detecte des qu'il y a un '/' dans la string cmd_short 
// DONE 4 : gerer les remises a -1 des fds dans les close_fds

int main(int argc, char **argv, char **envp)
{
	t_parse	*parsing;
	
	if (argc < 5)
	{
		ft_putstr_fd("Not enough arguments\n", STDERR_FILENO);
		return (-1);
	}
	parsing = __parse(argc, argv);
	if (parsing == NULL)
		return (-1);
	
	// __print_parse(parsing);
	// (void) envp;
	// __check_files_permissions(parsing);
	// str_tab = __get_path_var_tab(parsing->commands->next, envp);
	// printf("\npaths_list :\n");
	// __print_strtab(str_tab);
	__execute(parsing, envp);
	__free_parse(parsing);
	return (0);
}