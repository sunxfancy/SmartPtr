#ifndef SPTR_HPP
#define SPTR_HPP

#include <cstdio>
#include "memheap.hpp"

void* operator new (size_t size, MemHeap* ptr) {
    static MemHeap* p = MemHeap::getInstance();
    return p->alloc(size);
}


inline void sptr_ref(void* p) {
    MemHeap::ref(p);
}

inline void sptr_unref(void* p) {
    MemHeap::unref(p);
}


template<typename T>
class sptr {
public:
    sptr() {
    }

    sptr(bool b) {
    }

    sptr(T* p) {
        ptr = p;
    }

    sptr(const sptr<T>& p) {
        ptr = p.ptr;
        ref();
    }

    sptr<T>& operator=(T* p) {
        ptr = p;
        return *this;
    }

    sptr<T>& operator=(const sptr<T>& p) {
        ptr = p.ptr;
        ref();
        return *this;
    }

    ~sptr() {
        unref();
    }

    inline T* get() {
        return ptr;
    }

    inline void wrapper(T* p) {
        ptr = p;
    }
    inline T* unwrapper() {
        ref();
        return ptr;
    }

    T* operator -> () {
        return ptr;
    }
    T& operator * () {
        return *ptr;
    }

protected:
    inline void ref() {
        printf("ref\n");
        MemHeap::ref(ptr);
    }
    inline void unref() {
        printf("unref\n");
        MemHeap::unref(ptr);
    }

    T* ptr;
};


#endif /* end of include guard: SPTR_HPP */
