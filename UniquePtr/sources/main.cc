#include <iostream>

#include "unique_ptr.hh"

struct MYDEL {

};

int main() {
    custom_classes::unique_ptr<std::string []> my_ptr_1 = new std::string [1000];
    for (size_t i = 0; i < 1000; ++i) my_ptr_1[i] = "a" ;

    custom_classes::unique_ptr<int> my_ptr_2 = new int {3};
    custom_classes::unique_ptr<int> my_ptr_3 = new int {7};
    std::cout << *my_ptr_2 << " and " << *my_ptr_3 << std::endl;

    #ifdef COPY_TEST
        custom_classes::unique_ptr<int> my_ptr_4 = my_ptr_3;
    #else
        custom_classes::unique_ptr<int> my_ptr_4 = std::move(my_ptr_3);
    #endif
    std::cout << *my_ptr_2 << " and " << *my_ptr_4 << std::endl;

    #ifdef ASSIGNMENT_TEST
        my_ptr_3 = my_ptr_4;
    #else
        my_ptr_3 = std::move(my_ptr_4);
    #endif
    std::cout << *my_ptr_2 << " and " << *my_ptr_3 << std::endl;

    return 0;
}
