#ifndef MEM_HEAP_HPP
#define MEM_HEAP_HPP

#include <cstdlib>
#include <deque>

class MemHeap {

    // 内部使用的节点类型
    struct MemObjNode {
        size_t size;
        void* prev;
        void* next;
        size_t count;
        void* data[];
    };

public:
    MemHeap() {

    }

    inline static void ref (void* ptr) {
        MemObjNode* p = (MemObjNode*) ((char*) ptr - sizeof(MemObjNode));
        ++(p->count);
    }

    inline static void unref (void* ptr) {
        MemObjNode* p = (MemObjNode*) ((char*) ptr - sizeof(MemObjNode));
        --(p->count);
        if (p->count == 0) {
            free(p);
        }
    }

    inline void* alloc(size_t size) {
        MemObjNode* p = (MemObjNode*) malloc(size + sizeof(MemObjNode));
        p->next = NULL;
        p->count = 1;
        return &(p->data);
    }

    inline static MemHeap* getInstance() {
        static MemHeap instance;
        return &instance;
    }

    inline static int push_stack(void* ptr) {
        getInstance()->stack.push_back(ptr);
        return getInstance()->stack.size()-1;
    }

protected:
    std::deque<void*> stack;
    void* heap;
};



#endif /* end of include guard: MEM_HEAP_HPP */
