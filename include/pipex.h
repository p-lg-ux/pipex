/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgros <pgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 15:03:54 by pgros             #+#    #+#             */
/*   Updated: 2022/09/08 13:38:47 by pgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../lib42/lib42.h"
# include <stdlib.h>

typedef struct s_parse		t_parse;
typedef struct s_content	t_content;

struct s_parse{
	char	*infile;
	char	*outfile;
	t_list	*commands;
};

struct s_content{
	char	*cmd;
};

// UTILS
t_content	*__newcontent(char *cmd);
void		__free_content(void *c);
void		__print_content(t_content *content);

void		__free_parse(t_parse *parsing);
void		__print_parse(t_parse *parsing);

void		__print_lst(t_list *lst);

// PARSER
t_parse	*__parse(int argc, char **argv);

// EXECUTE
void	__execute(t_parse *parsing, char **envp);

#endif