#include "lem-in.h"

t_queue				*init_queue(void);
void				enqueue(t_queue *queue, void *content);
void				*dequeue(t_queue *queue);
void 				*peek_queue(t_queue *queue);
int					is_empty(t_queue *queue);
void				ft_print_queue(t_queue *queue);

t_queue				*init_queue(void)
{
	t_queue			*node;
	node = (t_queue *)ft_memalloc(sizeof(t_queue));
	node->first = NULL;
	node->last = NULL;
	return (node);
}

void				enqueue(t_queue *queue, void *content)
{
	t_list			*node;
	node = (t_list *)ft_memalloc(sizeof(t_list));
	node->content = content;
	node->next = NULL;
	// printf("node->content: %d\n", *(int *)node->content);
	if (!queue->last)
	{
		queue->last = node;
		queue->first = node;
		// printf("node->first: %zx\n", (size_t)queue->last);
		// printf("node->last: %zx\n", (size_t)queue->first);
	}
	else
	{
		queue->last->next = node;
		queue->last = queue->last->next;
	}
	return ;
}

void				*dequeue(t_queue *queue)
{
	t_list			*tmp;

	tmp = queue->first;
	if (!tmp)
	{
		printf("Empty queue\n");
		return (NULL);
	}
	else
	{
		printf("Resetting queue\n");
		queue->first = tmp->next;
		return (tmp->content);
	}

}

void 				*peek_queue(t_queue *queue)
{
	if (queue->first == NULL)
		return (NULL);
	return (queue->first->content);
}

int					is_empty(t_queue *queue)
{
	return (queue->first == NULL);
}

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
	int			i;
	t_graph		*graph;

	i = 0;
	graph = ft_memalloc(sizeof(t_graph));
	graph->total_vertices = vertices;
	// printf("graph->total_vertices: %d\n", vertices);
	graph->adj_lists = (t_node**)ft_memalloc(sizeof(t_node));
	graph->visited = ft_memalloc(sizeof(int) * vertices);
	while (i < vertices)
	{
		// printf("graph->adj_lists[i]: %d\n", (int)graph->adj_lists[i]);
		graph->adj_lists[i] = NULL;
		// printf("graph->visited[i]: %d\n\n", (int)graph->visited[i]);
		graph->visited[i] = 0;
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
	// printf("start_vertex before enqueue %d\n", start_vertex);
	ft_print_queue(queue);
	enqueue(queue, &start_vertex);
	// printf("start_vertex after enqueue %d\n", start_vertex);
	// ft_print_queue(queue);
	//printf("First print of queue: ");
	//ft_print_queue(queue);
	while (!is_empty(queue))
	{
		ft_print_queue(queue);
		int current_vertex;
		t_node *tmp;

		current_vertex = (int)dequeue(queue);
		printf("Visited %d nodes\n", current_vertex);
		tmp = graph->adj_lists[current_vertex];
		while (tmp)
		{
			int adj_vertex;

			adj_vertex = tmp->vertex;
			// printf("adj_vertex: %d\n", adj_vertex);
			if (graph->visited[adj_vertex] == 0)
			{
				graph->visited[adj_vertex] = 1;
				printf("%d\n", graph->visited[adj_vertex]);
				enqueue(queue, &adj_vertex);
				// printf("printing my queue: ");
				ft_print_queue(queue);
			}
			tmp = tmp->next;
		}
	}
}
