/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgros <pgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 16:09:34 by pgros             #+#    #+#             */
/*   Updated: 2022/09/30 16:22:01 by pgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

char	**__get_path_var_tab(char **envp)
{
	char	*path_str;
	char	**path_tab;
	int		i;

	i = -1;
	path_str = NULL;
	while (envp[++i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path_str = envp[i];
			break ;
		}
	}
	if (path_str == NULL)
		path_str = ft_strdup("");
	else
		path_str = ft_strtrim(path_str, "PATH=");
	if (path_str == NULL)
		return (perror("malloc"), NULL);
	path_tab = ft_split(path_str, ':');
	if (path_tab == NULL)
		return (perror("malloc"), free(path_str), NULL);
	free(path_str);
	return (path_tab);
}

int	__fill_paths_list(char **str_tab, char **path_var, t_llist *command)
{
	char	*str;
	int		i;

	i = 0;
	while (path_var[i] != NULL)
	{
		str = ft_strjoin(path_var[i], "/");
		if (str == NULL)
			return (perror("malloc"), -1);
		str_tab[i] = ft_strjoin(str, (__get_content(command))->cmd_short);
		if (str_tab[i] == NULL)
			return (perror("malloc"), free(str), -1);
		free(str);
		i++;
	}
	return (0);
}

char	**__get_paths_list(t_llist *command, char **envp)
{
	char	**str_tab;
	char	**path_var;
	int		len;
	int		ret;

	path_var = __get_path_var_tab(envp);
	if (path_var == NULL)
		return (NULL);
	len = __strtab_len(path_var);
	str_tab = ft_calloc(len + 1, sizeof(char *));
	if (str_tab == NULL)
		return (perror("malloc"), __free_strtab(path_var), NULL);
	ret = __fill_paths_list(str_tab, path_var, command);
	if (ret < 0)
		return (__free_strtab(str_tab), __free_strtab(path_var), NULL);
	__free_strtab(path_var);
	return (str_tab);
}
