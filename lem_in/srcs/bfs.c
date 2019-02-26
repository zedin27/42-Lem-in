/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcherret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 12:51:03 by tcherret          #+#    #+#             */
/*   Updated: 2019/02/25 20:41:29 by tcherret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static void		enqueue(int vertex, int **queue, t_farm *farm)
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

static int		dequeue(int **queue, t_farm *farm)
{
	int delete_item;

	if(farm->first == -1 || farm->first > farm->last)
	{
		ft_printf("Queue Underflow\n");
		exit(1);
	}
	delete_item = (*queue)[farm->first];
	farm->first = farm->first + 1;
	return (delete_item);
}

static int		is_empty(t_farm *farm)
{
	if (farm->first == -1 || farm->first > farm->last)
		return (1);
	else
		return (0);
}

static void		put_vertex_visited(int ind, t_farm *farm)
{
	int i;

	i = 0;
	while (farm->room[i].index != ind)
		i++;
	farm->room[i].visited = 1;
}

int		bfs(t_farm *farm)
{
	int		*queue;
	int		i;
	int		vertex;
	int		end;

	farm->first = -1;
	farm->last = -1;
	if (!(queue = malloc(sizeof(int*) * farm->nb_room)))
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
		ft_printf("Room visited = %s\n", farm->room[vertex].name);
		put_vertex_visited(vertex, farm);
		i = -1;
		while (++i < farm->nb_room)
			if (farm->link[vertex][i] == 1 && farm->room[i].visited == 0)
			{
				enqueue(i, &queue, farm);
				if (i == end)
				{
					ft_printf("Path found !!\n");
					return (1);
				}
			}
	}
	free(queue);
	return (-1);
}
