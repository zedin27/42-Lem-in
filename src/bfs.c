#include "lem-in.h"

t_queue				*init_queue(void);
void				enqueue(t_queue *queue, void *content);
int					dequeue(t_queue *queue);
void 				*peek_queue(t_queue *queue);
int					is_empty(t_queue *queue);
void				ft_print_queue(t_queue *queue);

void				ft_print_queue(t_queue *queue)
{
	t_list *tmp;

	if (is_empty(queue))
		ft_putstr("Empty queue in ft_print_queue\n");
	else
	{
		ft_putstr("\nQueue contains: \n");
		while (queue->first != NULL)
		{
			tmp = queue->first;
			// ik-todo: check dereference
			char print = *(char *)tmp->content;
			printf("%c\n", print);
			queue->first = tmp->next;
		}
	}
}

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
	if (!queue->last)
	{
		queue->last = node;
		queue->first = node;

	}
	else
	{
		queue->last->next = node;
		queue->last = queue->last->next;
	}
	return ;
}

int					dequeue(t_queue *queue)
{
	t_list			*tmp;

	ft_putstr("before tmp\n");
	tmp = queue->first;
	ft_putstr("after tmp\n");
	if (!tmp)
	{
		ft_putstr("Empty queue in dequeue\n");
		return (0); // Maybe here?
	}
	else
	{
		printf("Resetting queue\n");
		queue->first = tmp->next;
		return (*(int *)tmp->content);
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
	return (queue->first == NULL || queue->last == NULL);
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
	graph->adj_lists = (t_node**)ft_memalloc(sizeof(t_node*) * vertices);
	graph->visited = ft_memalloc(sizeof(int) * vertices);
	while (i < vertices)
	{
		graph->adj_lists[i] = NULL;
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
	enqueue(queue, &start_vertex);
	while (!is_empty(queue))
	{
		int current_vertex;
		t_node *tmp;

		current_vertex = dequeue(queue);
		ft_putstr("after current_vertex dequeue\n");
		tmp = graph->adj_lists[current_vertex];
		while (tmp)
		{
			int adj_vertex;

			adj_vertex = tmp->vertex;
			if (graph->visited[adj_vertex] == 0)
			{
				graph->visited[adj_vertex] = 1;
				printf("test %d\n", adj_vertex);
				enqueue(queue, &adj_vertex);
			}
			tmp = tmp->next;
		}
	}
}
