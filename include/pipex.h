/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgros <pgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 15:03:54 by pgros             #+#    #+#             */
/*   Updated: 2022/09/27 15:40:57 by pgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../lib42/lib42.h"
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct s_parse		t_parse;
typedef struct s_content	t_content;
typedef enum e_do_close		t_do_close;

struct s_parse{
	char	*infile;
	char	*outfile;
	t_llist	*commands;
};

struct s_content{
	char	*cmd;
	char	*cmd_short;
	char	**arg;
	char	*path;
	int		fds_in[2];
	int		fds_out[2];
	t_parse	*parsing;
};

enum e_do_close{
	DONT_CLOSE_FDS	= 0,
	CLOSE_FDS		= 1,
};

// UTILS
void		__free_strtab(char **tab);
int			__strtab_len(char **tab);
void		__print_strtab(char **tab);

t_content	*__newcontent(char *cmd);
void		__free_content(void *c);
void		__print_content(t_content *content);
t_content	*__get_content(t_llist *command);

void		__free_parse(t_parse *parsing);
void		__print_parse(t_parse *parsing);
// int			__check_files_permissions(t_parse *parsing);

void		__print_llst(t_llist *llst);

// PARSER
t_parse		*__parse(int argc, char **argv);

// EXECUTE

//	execute.c
void		__execute(t_parse *parsing, char **envp);
void		__fork_process(t_llist *command, char **envp);
void		__pipe_it(t_llist *command);

//	child_process.c
void		__duplicate_fds(t_llist *command);
void		__child_process(t_llist *command, char **envp);

//	find_path.c
char		**__get_path_var_tab(char **envp);
char		**__get_paths_list(t_llist *command, char **envp);
void		__fill_paths_list(char ***str_tab, char **path_var,
				t_llist *command);
void		__command_error(t_llist *command, char **paths_list);
void		__find_command_path(t_llist *command, char **envp);

//	open_fds.c
void		__open_infile(t_llist *command);
void		__open_outfile(t_llist *command);
void		__open_files(t_llist *command);

//	ultimate_exit.c
void		__close_all_fds(t_llist *command);
void		__close_fds_out(t_llist *command);
void		__close_fds_in(t_llist *command);
void		__ultimate_exit(t_llist *command, char *message,
				t_do_close do_close_fds);

#endif