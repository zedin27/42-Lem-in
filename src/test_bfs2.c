#include "lem-in.h"

t_queue				*init_queue(void);
void				enqueue(t_queue *queue, void *content);
void				*dequeue(t_queue *queue);
void 				*peek_queue(t_queue *queue);
int					is_empty(t_queue *queue);
void				print();

struct s_node *new_node()
{
	struct s_node *node;
	node = (struct s_node*)ft_memalloc(sizeof(struct s_node));
	node->info = NULL;
	node->next = NULL;

	if (node != NULL)
		return (node);
	else
	{
		printf("overflow\n");
		exit(1);
	}
}

int		dequeue()
{
	int item;
	if (front == NULL)
	{
		printf("queue underflow");
		exit (1);
	}
	temp = front;
	item = temp->info;
	front = front->next;
	if (front == NULL)
		rear = NULL;
	free (temp);
}

void	enqueue(int item)
{
	struct s_node = new_node();
	node->info = item;
	if (front == NULL)
	{
		front = node;
		rear = node;
	}
	else
	{
		rear->next = node;
		rear = node;
	}
	return ;
}

void		print()
{
	if (front==NULL)
	{
		printf("\nQueue is empty\n");
		return;
	}
	ptr = front;
	printf("\n\nThe linked list implementation of queue :\n\n");
	while(ptr)
	{
		printf("%d->",ptr->info);
		ptr=ptr->next;
	}
	printf("NULL\n");
	return;
}

int					is_empty(t_queue *queue)
{
	return (rear == NULL);
}

struct s_node				*create_node(int val)
{
	struct s_node		*new_node;

	new_node = (struct s_node*)ft_memalloc(sizeof(struct s_node));
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
	graph->adj_lists = (struct s_node**)ft_memalloc(sizeof(struct s_node));
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
	struct s_node		*new_node;

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
	print();
	enqueue(&start_vertex);
	while (!is_empty(queue))
	{
		ft_print_queue(queue);
		int current_vertex;
		struct s_node *tmp;

		current_vertex = (int)dequeue();
		printf("Visited %d nodes\n", current_vertex);
		tmp = graph->adj_lists[current_vertex];
		while (tmp)
		{
			int adj_vertex;

			adj_vertex = tmp->vertex;
			if (graph->visited[adj_vertex] == 0)
			{
				graph->visited[adj_vertex] = 1;
				printf("%d\n", graph->visited[adj_vertex]);
				enqueue(&adj_vertex);
				print(queue);
			}
			tmp = tmp->next;
		}
	}
}
