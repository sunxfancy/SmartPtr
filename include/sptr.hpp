#ifndef SPTR_HPP
#define SPTR_HPP

#include "memheap.hpp"

void* operator new (size_t size, MemHeap* ptr) {
    if (ptr) return ptr->allocate(size);
    static MemHeap* p = MemHeap::getInstance();
    return p->allocate(size);
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
        ptr = NULL;
        printf("sptr\n");
    }

    sptr(T* p) {
        ptr = p;
        printf("sptr T*\n");

    }

    sptr(const sptr<T>& p) {
        ptr = p.ptr;
        ref();
        printf("sptr const&\n");

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
        if (ptr) MemHeap::ref(ptr);
    }
    inline void unref() {
        if (ptr) MemHeap::unref(ptr);
    }

    T* ptr;
};

template<typename T>
class sptr_stack : public sptr<T> {
public:
    sptr_stack() : sptr<T>() {
    }

    sptr_stack(T* p) : sptr<T>(p)  {
    }

    sptr_stack(const sptr<T>& p) : sptr<T>(p) {
    }

    ~sptr_stack() {
        sptr<T>::unref();
    }
};


#endif /* end of include guard: SPTR_HPP */
