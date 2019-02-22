#include "lem-in.h"

t_node				*create_node(int val)
{
	t_node		*new_node;

	new_node = (t_node*)ft_memalloc(sizeof(t_node));
	new_node->vertex = val;
	new_node->next = NULL;
	return (new_node);
}

t_graph				*create_graph(int vertices)
{
	t_graph		*graph;
	int			i;

	i = 0;
	graph = (t_graph*)ft_memalloc(sizeof(t_graph));
	graph->total_vertices = vertices;
	graph->adj_lists = (t_graph*)ft_memalloc(sizeof(t_node*) * vertices);
	graph->visited = (t_graph*)ft_memalloc(sizeof(int) * vertices);
	while (i < vertices)
	{
		graph->adj_lists[i] = NULL;
		graph->visited = 0;
		i++;
	}
	return (graph);
}

void 				add_edge(t_graph *graph, int src, int dst)
{
	t_node		*new_node;

	new_node = create_node(dst);
	new_node->next = graph->adj_lists[src];
	graph->adj_lists[src] = new_node;

	new_node = create_node(src);
	new_node->next = graph->adj_lists[dst];
	graph->adj_lists[dst] = new_node;
}

void				bfs(t_graph *graph, int start_vertex)
{
	t_queue *queue;

	queue = init_queue();
	graph->visited[start_vertex] = 1;
	enqueue(queue, start_vertex);
	while (!is_empty(&queue))
	{
		print_queue(&queue);
		int current_vertex;
		t_node *tmp;

		current_vertex = dequeue(&queue);
		printf("Visited %d\n", current_vertex);
		tmp = graph->adj_lists[current_vertex];
		while (tmp)
		{
			int adj_vertex;

			adj_vertex = tmp->vertex;
			if (graph->visited[adj_vertex] == 0)
			{
				graph->visited[adj_vertex] = 1;
				enqueue(&queue, adj_vertex);
			}
			tmp = tmp->next;
		}
	}
}
