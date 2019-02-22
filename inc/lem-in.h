# ifndef LEM_IN
# define LEM_IN

# include "../libft/libft.h"
# include <errno.h>

/*
** Node
*/

typedef struct		s_node
{
	struct s_node	*next;
	int				vertex;
}					t_node;

/*
** Graph
*/

typedef struct		s_graph
{
	t_node			**adj_lists;
	int				*visited;
	int				total_vertices;
}					t_graph;

t_node				*create_node(int vertex);
t_graph				*create_graph(int vertices);
void				add_edge(t_graph *graph, int src, int dst);
void				bfs(t_graph *graph, int start_vertex);

# endif
