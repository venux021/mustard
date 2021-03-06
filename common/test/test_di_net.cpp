#include "common/graph.h"
#include "common/matrix2.h"
using namespace mustard;

int main()
{
    // typedef matrix::common_matrix<int> cm_t;
    // typedef graph::adj_list<int> st_t;
    typedef graph::orthogonal_list<int> st_t;
    typedef graph::directed_network<char, int, st_t>  d_net;
    d_net * n1 = graph::read_network<d_net>();
    n1->display(std::cout);
    delete n1;
    return 0;
}
