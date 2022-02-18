# First task. My unique_ptr

## To run Hometasks files have been created with CMake, so it will be enough to run:
```
mkdir build && cd build
cmake ..
make
./main
```
## To use some tests compile with(in ./build/ directory):
```
g++ ../sources/main.cc -o main -DCOPY_TEST
g++ ../sources/main.cc -o main -DASSIGNMENT_TEST
```
## Or if you use clang:
```
clang++ ../sources/main.cc -o main -DCOPY_TEST
clang++ ../sources/main.cc -o main -DASSIGNMENT_TEST
```
