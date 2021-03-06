# SmartPtr
C++ smart pointer library with GC


It's hard for C++ to manange memory, because of the downward compatibility for C. We usually use smart pointer based on reference count to prevent the memory leak, but it's useless when come across the circular reference.

So I want to design a kind of smart pointer with GC, that sometimes will free the memory which is in the status of circular reference. 


## Design

The fundamental of this smart pointer is the reference count, but we store the reference number in front of the memory.

![pointer](asserts/ptr.png)

We have a global singleton manager to alloc memory. When the smart pointer were constructed on the stack, it would register the pointer to the manager.

```c

struct MemObjNode {
    size_t size;
    int count;
    void* data[];
};

```


The meta is used to scan the pointer in its data, so we have to know the size about the memory. The next and prev pointers constitute a double linked list which can know the memories it alloced.

Besides the metadata, other parts will be regraded as an array full of pointers. We should test all the pointers in it and find the right pointer we alloced.



Here our demo:

```cpp

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

```

After running:

```
allocate 0x1716cf0
release 0x1716cf0
allocate 0x1716cf0
release 0x1716cf0
```
