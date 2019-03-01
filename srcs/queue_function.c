/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcherret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 16:48:44 by tcherret          #+#    #+#             */
/*   Updated: 2019/02/28 15:15:17 by tcherret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	enqueue(int vertex, int **queue, t_farm *farm)
{
	if (farm->last == farm->nb_room - 1)
		ft_printf("Queue Overflow\n");
	else
	{
		if (farm->first == -1)
			farm->first = 0;
		farm->last = farm->last + 1;
		(*queue)[farm->last] = vertex;
	}
}

int		dequeue(int **queue, t_farm *farm)
{
	int delete_item;

	if (farm->first == -1 || farm->first > farm->last)
	{
		ft_printf("Queue Underflow\n");
		exit(1);
	}
	delete_item = (*queue)[farm->first];
	farm->first = farm->first + 1;
	return (delete_item);
}

int		is_empty(t_farm *farm)
{
	if (farm->first == -1 || farm->first > farm->last)
		return (1);
	else
		return (0);
}

void	put_vertex_visited(int ind, t_farm *farm)
{
	int i;

	i = 0;
	while (farm->room[i].index != ind)
		i++;
	farm->room[i].visited = 1;
}

int		check_enqueue(int *queue, int i, t_farm *farm)
{
	int j;

	j = 0;
	while (j < farm->nb_room)
	{
		if (queue[j] == i)
			return (0);
		j++;
	}
	return (1);
}
