cmake_minimum_required (VERSION 3.4)
project (unittests)

include_directories (../..)

# sort_test部分
set (SORT_TEST_SRC sort_test.cpp)
set (SORT_INC ../sort.h)

source_group ("src" FILES ${SORT_TEST_SRC})
source_group ("include" FILES ${SORT_INC})

add_executable (sort_test ${SORT_TEST_SRC} ${SORT_INC})

# linearlist_test部分
set (LINEARLIST_TEST_SRC linearlist_test.cpp)
set (LINEARLIST_INCS ../forward_list.h ../list.h)

source_group ("src" FILES ${LINEARLIST_TEST_SRC})
source_group ("include" FILES ${LINEARLIST_INCS})

add_executable (linearlist_test ${LINEARLIST_TEST_SRC} ${LINEARLIST_INCS})
