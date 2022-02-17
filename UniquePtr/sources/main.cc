#include <iostream>

#include "../include/unique_ptr.hh"

int main() {
    custom_classes::unique_ptr<int> my_ptr = new int {5};
    return 0;
}
