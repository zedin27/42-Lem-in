/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcherret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 12:51:03 by tcherret          #+#    #+#             */
/*   Updated: 2019/02/26 19:15:31 by tcherret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static void		print_queue(int *queue, t_farm *farm)
{
		int i;

		ft_printf("QUEUE == "); //print_queue
		i = -1;
		while (++i <= farm->last)
			ft_printf("%d ", queue[i]);
		ft_printf("\n");
}

static void		print_shortest(int *path, t_farm *farm)
{

}

int		bfs(t_farm *farm)
{
	int		*queue;
	int		*path;
	int		i;
	int		vertex;
	int		end;

	farm->first = -1;
	farm->last = -1;
	if (!(queue = ft_memalloc(sizeof(int*) * farm->nb_room)))
		return (-1);
	if (!(path = ft_memalloc(sizeof(int*) * farm->nb_room)))
		return (-1);
	i = 0;
	while (farm->room[i].start == 0)
		i++;
	enqueue(i, &queue, farm);
	i = 0;
	while (farm->room[i].end == 0)
		i++;
	end = i;
	while (!is_empty(farm))
	{
		vertex = dequeue(&queue, farm);
		put_vertex_visited(vertex, farm);
		i = 0;
		ft_printf("Room %s visited!\n", farm->room[vertex].name);
		while (i < farm->nb_room)
		{
			if (farm->link[vertex][i] == 1 && farm->room[i].visited == 0)
			{
				if (check_enqueue(queue, i, farm) == 1)
					enqueue(i, &queue, farm);
				if (i == end)
				{
					ft_printf("Room %s visited!\n", farm->room[end].name);
					print_shortest(queue, farm);
					return (1);
				}
			}
			i++;
		}
	}
	free(queue);
	return (0);
}
