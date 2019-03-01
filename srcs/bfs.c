/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcherret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 12:51:03 by tcherret          #+#    #+#             */
/*   Updated: 2019/03/01 14:31:37 by tcherret         ###   ########.fr       */
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

static void		create_path(int **path, int *queue, t_farm *farm, int nb)
{
	int weight;
	int room_after;
	int j;

	weight = nb;
	nb--;
	farm->count--;
	(*path)[nb] = queue[farm->count];
	j = nb - 1;
	room_after = queue[farm->count];
	while (farm->count >= 0)
	{
		if (farm->room[queue[farm->count]].weight == weight - 1
				&& farm->link[queue[farm->count]][room_after] == 1)
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
}

static int		path_found(t_farm *farm, int **queue, int end, int vertex)
{

	//ft_printf("Room visited is %s and weight = %d\n", farm->room[end].name, farm->room[vertex].weight + 1);
	farm->room[end].weight = farm->room[vertex].weight + 1;
	if (!(farm->path[farm->nb_path].path = ft_memalloc(sizeof(int*) * (farm->room[end].weight)))) // to free
		return (-1);
	create_path(&farm->path[farm->nb_path].path,
			*queue, farm, farm->room[end].weight);
	farm->path[farm->nb_path].weight = farm->room[end].weight;
	ft_printf("Weight is %d and path is: ", farm->room[end].weight);
	print_path(farm->path[farm->nb_path].path, farm->room[end].weight);
	free(*queue);
	return (1);
}

static void		reset_before_bfs(t_farm *farm)
{
	int i;

	i = -1;
	while (++i < farm->nb_room)
		farm->room[i].visited = 0;
	farm->first = -1;
	farm->last = -1;
}

static void		initialization_bfs(t_farm *farm, int **queue, int *end)
{
	int i;

	i = 0;
	while (farm->room[i].start == 0)
		i++;
	farm->room[i].weight = 1;
	enqueue(i, queue, farm);
	farm->count = 1;
	i = 0;
	while (farm->room[i].end == 0)
		i++;
	*end = i;
}

static void		gain_space(t_farm *farm, int **queue, int i, int vertex)
{
	farm->count++;
	enqueue(i, queue, farm);
	farm->room[i].weight = farm->room[vertex].weight + 1;

}

static void		prepare_loop(t_farm *farm, int **queue, int *vertex, int *i)
{
		*vertex = dequeue(queue, farm);
		put_vertex_visited(*vertex, farm);
		//ft_printf("Room visited is %s and weight = %d\n", farm->room[vertex].name, farm->room[vertex].weight);
		*i = -1;
}

int				bfs(t_farm *farm)
{
	int		*queue;
	int		i;
	int		vertex;
	int		end;

	reset_before_bfs(farm);
	if (!(queue = ft_memalloc(sizeof(int*) * farm->nb_room)))
		return (-1);
	initialization_bfs(farm, &queue, &end);
	while (!is_empty(farm))
	{
		prepare_loop(farm, &queue, &vertex, &i);
		while (++i < farm->nb_room)
		{
			if (farm->link[vertex][i] == 1 && farm->room[i].visited == 0)
			{
				if (check_enqueue(queue, i, farm) == 1)
					gain_space(farm, &queue, i, vertex);
				if (i == end)
					return (path_found(farm, &queue, end, vertex));
			}
		}
	}
	free(queue);
	return (0);
}
