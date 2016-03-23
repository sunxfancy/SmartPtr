#ifndef MEM_HEAP_HPP
#define MEM_HEAP_HPP

#include <cstdlib>
#include <deque>
#include <cstdio>

class MemHeap {

    // 内部使用的节点类型
    struct MemObjNode {
        size_t size;
        MemObjNode* prev;
        MemObjNode* next;
        size_t count;
        void* data[];
    };

public:
    MemHeap() {

    }

    inline static void ref (void* ptr) {
        printf("ref %p\n", ptr);
        MemObjNode* p = (MemObjNode*) ((char*) ptr - sizeof(MemObjNode));
        ++(p->count);
    }

    inline static void unref (void* ptr) {
        printf("unref %p\n", ptr);
        MemObjNode* p = (MemObjNode*) ((char*) ptr - sizeof(MemObjNode));
        --(p->count);
        if (p->count == 0) {
            free(p);
            printf("free %p\n", p);
        }
    }

    void* allocate(size_t size) {
        MemObjNode* p = (MemObjNode*) malloc(size + sizeof(MemObjNode));
        if (p == NULL) return NULL;
        p->size = size;
        p->prev = NULL;
        p->next = NULL;
        p->count = 1;
        printf("ref %p\n", &(p->data));
        return &(p->data);
    }

    void release(void* ptr) {
        if (ptr == NULL) return;
        MemObjNode* p = (MemObjNode*) ((char*) ptr - sizeof(MemObjNode));
        if (p->prev) p->prev->next = p->next;
        if (p->next) p->next->prev = p->prev;
        free(ptr);
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
