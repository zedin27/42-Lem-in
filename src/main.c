#include "lem-in.h"
#include "../libft/libft.h"
#include <stdio.h>

int main(void)
{

	t_graph *graph;
	printf("\n\n\nTesting my lem-in output: \n\n");
	graph = create_graph(6);
	add_edge(graph, 0, 1);
    add_edge(graph, 0, 2);
    add_edge(graph, 1, 2);
    add_edge(graph, 1, 4);
    add_edge(graph, 1, 3);
    add_edge(graph, 2, 4);
    add_edge(graph, 3, 4);
	bfs(graph, 0);
	return (0);
}
