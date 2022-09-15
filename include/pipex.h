/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgros <pgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 15:03:54 by pgros             #+#    #+#             */
/*   Updated: 2022/09/15 17:47:19 by pgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../lib42/lib42.h"
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>

typedef struct s_parse		t_parse;
typedef struct s_content	t_content;

struct s_parse{
	char	*infile;
	char	*outfile;
	t_list	*commands;
};

struct s_content{
	char	*cmd;
	char	*cmd_short;
	char	**arg;
	char	*path;
	int		fds_in[2];
	int		fds_out[2];
};

// UTILS
void		__free_strtab(char **tab);
int			__strtab_len(char **tab);
void		__print_strtab(char **tab);

t_content	*__newcontent(char *cmd);
void		__free_content(void *c);
void		__print_content(t_content *content);
t_content	*__get_content(t_list *command);

void		__free_parse(t_parse *parsing);
void		__print_parse(t_parse *parsing);
int			__check_files_permissions(t_parse *parsing);

void		__print_lst(t_list *lst);

// PARSER
t_parse		*__parse(int argc, char **argv);

// EXECUTE
void		__execute(t_parse *parsing, char **envp);

char		**__get_path_var_tab(char **envp);
char		**__get_paths_list(t_list *command, char **envp);
void		__fill_paths_list(char **str_tab, char **path_var,
				t_list *command);

#endif