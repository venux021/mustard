#include "common/graph.h"
using namespace mustard;

typedef graph::adj_list<bool> list_t;
typedef graph::undirected_graph<char,list_t> graph_t;

void print_articulation_points(graph_t * g);

