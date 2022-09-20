/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llst_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgros <pgros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 17:48:16 by pgros             #+#    #+#             */
/*   Updated: 2022/09/20 14:40:53 by pgros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

void	__print_llst(t_llist *llst)
{
	t_content *content;

	while (llst != NULL)
	{
		content = llst->content;
		__print_content(content);
		ft_printf("\n");
		llst = llst->next;
	}
}
