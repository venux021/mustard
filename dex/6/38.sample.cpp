#include "common/bitree.h"
#include <stack>
using namespace mustard;

typedef bitree::node<char> node_t;

void print_post_order(node_t * root)
{
    std::stack<node_t*> stk;
    std::stack<int> flags;
    node_t * p = root;
    while (p || !stk.empty()) {
        while (p) {
            stk.push(p);
            flags.push(0);
            p = p->lc;
        }

        if (!flags.top()) {
            flags.top() = 1;
            p = stk.top()->rc;
        } else {
            std::cout << stk.top()->data << ' ';
            stk.pop();
            flags.pop();
        }
    }

    std::cout << '\n';
}
