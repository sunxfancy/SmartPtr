#include "../include/sptr.hpp"

class Test {
public:
    sptr<Test> next;
};



int main(int argc, char const *argv[]) {
    sptr<Test> p = new (MemHeap::getInstance()) Test();
    p->next = p;
    return 0;
}
