cmake_minimum_required(VERSION 3.4)
project(unittests)

include_directories(../..)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-g)
endif()

set(UNITTESTS_SRCS
    algo_gtest.cpp
    sort_gtest.cpp
)

set(UNITTESTS_INCS
    ../kmp.h
    ../lru.h
    ../qsort.h
    ../sort.h
    ../trie.h
)

source_group("src" FILES ${UNITTESTS_SRCS})
source_group("include" FILES ${UNITTESTS_INCS})

add_executable(uts ${UNITTESTS_SRCS} ${UNITTESTS_INCS})
target_link_libraries(uts gtest gtest_main pthread)
