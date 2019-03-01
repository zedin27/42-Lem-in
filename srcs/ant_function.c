/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant_function.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcherret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 19:15:38 by tcherret          #+#    #+#             */
/*   Updated: 2019/02/28 15:16:05 by tcherret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int		move_ant(t_room *src, t_room *dst)
{
	if (src->ant == 1 && dst->ant == 0)
	{
		src->ant = 0;
		dst->ant = 1;
		return (1);
	}
	else
		return (0);
}

int		check_room_free(t_room *room)
{
	if (room->ant == 0)
		return (1);
	else
		return (0);
}

int		graph_finished(t_farm *farm)
{
	int i;

	i = 0;
	while (i < farm->nb_room)
	{
		if (farm->room[i].end != 1)
		{
			if (farm->room[i].ant != 0)
				return (-1);
		}
		else if (farm->room[i].end == 1)
			if (farm->room[i].ant != farm->total)
				return (-1);
		i++;
	}
	return (1);
}
