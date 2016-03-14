#ifndef MEM_HEAP_HPP
#define MEM_HEAP_HPP

#include <cstdlib>
#include <deque>

class MemHeap {

    // 内部使用的节点类型
    struct MemObjNode {
        void* next;
        unsigned int count;
        char data[1];
    };

public:
    MemHeap() {

    }

    inline static void ref (void* ptr) {
        MemObjNode* p = (MemObjNode*) ptr;
        ++(p->count);
    }

    inline static void unref (void* ptr) {
        MemObjNode* p = (MemObjNode*) ptr;
        --(p->count);
        if (p->count == 0) {
            free(p);
        }
    }

    inline void* alloc(size_t size) {
        MemObjNode* p = (MemObjNode*) malloc(size
            + sizeof(unsigned int) + sizeof(void*));
        p->next = NULL;
        p->count = 1;
        return &(p->data);
    }

    inline static MemHeap* getInstance() {
        static MemHeap instance;
        return &instance;
    }

    inline static void push_stack(void* ptr) {
        getInstance()->stack.push_back(ptr);
    }

protected:
    std::deque<void*> stack;
    void* heap = NULL;
};



#endif /* end of include guard: MEM_HEAP_HPP */
