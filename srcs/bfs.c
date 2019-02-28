/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcherret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 12:51:03 by tcherret          #+#    #+#             */
/*   Updated: 2019/02/28 13:14:10 by tcherret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*static void		print_queue(int *queue, t_farm *farm)
{
	int i;

	ft_printf("QUEUE == "); //print_queue
	i = -1;
	while (++i <= farm->last)
		ft_printf("%d ", queue[i]);
	ft_printf("\n");
}*/

static void		print_path(int *path, int nb)
{
	int i;

	i = -1;
	while (++i < nb)
		ft_printf("%d ", path[i]);
	ft_printf("\n");
}

int		create_path(int **path, int *queue, t_farm *farm, int nb)
{
	int weight;
	int room_after;
	int j;

	weight = nb;
	nb--;
	farm->count--;
	j = nb;
	(*path)[j] = queue[farm->count];
	j--;
	room_after = queue[farm->count];
	while (farm->count >= 0)
	{
		if (farm->room[queue[farm->count]].weight == weight - 1 && farm->link[queue[farm->count]][room_after] == 1)
		{
			farm->link[queue[farm->count]][room_after] = -1;
			farm->link[room_after][queue[farm->count]] = -1;
			(*path)[j] = queue[farm->count];
			room_after = queue[farm->count];
			weight = farm->room[queue[farm->count]].weight;
			j--;
		}
		nb--;
		farm->count--;
	}
	return (1);
}

int		bfs(t_farm *farm)
{
	int		*queue;
	int		i;
	int		vertex;
	int		end;
	int		*path;

	i = -1;
	while (++i < farm->nb_room)
		farm->room[i].visited = 0;
	i = 0;
	farm->first = -1;
	farm->last = -1;
	if (!(queue = ft_memalloc(sizeof(int*) * farm->nb_room)))
		return (-1);
	i = 0;
	while (farm->room[i].start == 0)
		i++;
	farm->room[i].weight = 1;
	enqueue(i, &queue, farm);
	farm->count = 1;
	i = 0;
	while (farm->room[i].end == 0)
		i++;
	end = i;
	while (!is_empty(farm))
	{
		vertex = dequeue(&queue, farm);
		put_vertex_visited(vertex, farm);
		//ft_printf("Room visited is %s and weight = %d\n", farm->room[vertex].name, farm->room[vertex].weight);
		i = 0;
		while (i < farm->nb_room)
		{
			//ft_printf("Link is %d between %s et %s\n", farm->link[vertex][i], farm->room[i].name, farm->room[vertex].name);
			if (farm->link[vertex][i] == 1 && farm->room[i].visited == 0)
			{
				if (check_enqueue(queue, i, farm) == 1)
				{
					farm->count++;
					enqueue(i, &queue, farm);
					farm->room[i].weight = farm->room[vertex].weight + 1;
				}
				if (i == end)
				{
					//ft_printf("Room visited is %s and weight = %d\n", farm->room[end].name, farm->room[vertex].weight + 1);
					farm->room[end].weight = farm->room[vertex].weight + 1;
					if (!(path = ft_memalloc(sizeof(int*) * (farm->room[end].weight)))) //remplace path directly by farm->
						return (-1);
					create_path(&path, queue, farm, farm->room[end].weight);
					farm->path[farm->nb_path].path = path; // to free
					farm->path[farm->nb_path].weight = farm->room[end].weight;
					ft_printf("Weight is %d and path is: ", farm->room[end].weight);
					print_path(farm->path[farm->nb_path].path, farm->room[end].weight);
					free(queue);
					//free(path);
					return (1);
				}
			}
			i++;
		}
	}
	free(queue);
	return (0);
}
