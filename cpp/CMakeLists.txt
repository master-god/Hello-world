cmake_minimum_required(VERSION 3.20.0)

project (codes)

add_executable(a a.cpp) 
add_executable(b b.cpp) 
add_executable(c c.cpp)
add_executable(d all_fit's.cpp)
add_executable(e dsu_kruskal.cpp)
add_executable(f tilting.cpp)
add_executable(g shell_sort.cpp)
add_executable(h d.cpp)

enable_testing()

add_test(test1 a) 
add_test(test2 b) 
add_test(test3 c)
add_test(test4 d)
add_test(test5 e)
add_test(test6 f)
add_test(test7 g)
add_test(test8 h)