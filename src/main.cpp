#include "../include/sptr.hpp"

class Test {
public:
    sptr<Test> next;
};

int test() {
    sptr_stack<Test> p = new (MemHeap::getInstance()) Test();
    return 0;
}


int main(int argc, char const *argv[]) {
    test();
    sptr_stack<Test> p = new (MemHeap::getInstance()) Test();
    p->next = p;
    p = NULL;
    MemHeap::runGC();

    return 0;
}
