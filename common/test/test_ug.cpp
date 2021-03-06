#include "common/graph.h"
using namespace mustard;

int main()
{
    // typedef matrix::symmetric_matrix<bool> st_t;
    typedef graph::adj_list<bool> st_t;
    typedef graph::undirected_graph<char, st_t> g_t;

    g_t * graph = graph::read_graph<g_t>();
    graph->display(std::cout);

    delete graph;
    return 0;
}
