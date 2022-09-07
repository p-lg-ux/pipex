/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgros <pgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 17:48:16 by pgros             #+#    #+#             */
/*   Updated: 2022/09/07 20:09:19 by pgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

void	__print_lst(t_list *lst)
{
	t_content *content;

	while (lst != NULL)
	{
		content = lst->content;
		__print_content(content);
		lst = lst->next;
	}
}
