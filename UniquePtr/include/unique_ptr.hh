#ifndef __UNIQUE_PTR_HH__
#define __UNIQUE_PTR_HH__
#include <iostream>
#include <memeory>

namespace custom_classes {

// TODO: operators [], (), ->

// make special functor right constructor (but anyway we're having some problems with dataT * in fields)

// deletor functor for pointers on elements
template <typename dataT>
struct default_delete {
    void operator(dataT *ptr) () { delete ptr; }
};

// deletor functor for pointers on arrays
template <typename dataT>
struct default_delete<dataT[]> {
    void operator()(dataT *ptr) () {delete [] ptr; }
};

// unique_ptr class
template <typename dataT, typename Deleter = default_delete<dataT>>
struct unique_ptr final {
private:
    dataT   *ptr_;
    Deleter del_;
public:
    unique_ptr(dataT *) : ptr_(ptr_) {}
    unique_ptr(const unique_ptr &other) = delete;
    unique_ptr &operator=(const unique_ptr &other) = delete;
    unique_ptr(unique_ptr &&other) : ptr_(other.ptr_) { other.ptr_ = nullptr; }
    unique_ptr &operator=(unique_ptr &&other) {  }
    ~unique_ptr { del_(ptr_); }
};

}

#endif
