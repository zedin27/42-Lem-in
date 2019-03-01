/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_room.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcherret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 15:42:22 by tcherret          #+#    #+#             */
/*   Updated: 2019/02/28 15:14:52 by tcherret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int		ft_realloc_room(t_farm farm, int old_nb_room)
{
	int		j;
	t_room	*tmp;

	j = 0;
	if (!(tmp = malloc(sizeof(t_room) * (farm.size * 2))))
		return (-1);
	farm.size = farm.size * 2;
	while (j < old_nb_room)
	{
		tmp[j] = farm.room[j];
		j++;
	}
	free(farm.room);
	farm.room = tmp;
	return (0);
}
