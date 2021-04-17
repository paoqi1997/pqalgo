cmake_minimum_required(VERSION 3.4)
project(unittests)

include_directories(../..)

set(UNITTESTS_SRC
    sort_gtest.cpp
)

set(UNITTESTS_INC
    ../sort.h
)

source_group("src" FILES ${UNITTESTS_SRC})
source_group("include" FILES ${UNITTESTS_INC})

add_executable(uts ${UNITTESTS_SRC} ${UNITTESTS_INC})
target_link_libraries(uts gtest gtest_main pthread)
