cmake_minimum_required (VERSION 3.4)
project (unittests)

include_directories (../..)

# sort_test部分
set (SORT_TEST_SRC sort_test.cpp)
set (SORT_INC ../sort.h)

source_group ("src" FILES ${SORT_TEST_SRC})
source_group ("include" FILES ${SORT_INC})

add_executable (sort_test ${SORT_TEST_SRC} ${SORT_INC})

# structures_test部分
set (STRUCTURES_TEST_SRC structures_test.cpp)
set (STRUCTURES_INCS ../forward_list.h)

source_group ("src" FILES ${STRUCTURES_TEST_SRC})
source_group ("include" FILES ${STRUCTURES_INCS})

add_executable (structures_test ${STRUCTURES_TEST_SRC} ${STRUCTURES_INCS})
