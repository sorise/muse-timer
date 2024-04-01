cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

add_executable(tree_ut treeTimer_ut.cpp)
add_executable(wheel_ut wheelTimer_ut.cpp)


target_link_libraries(tree_ut
        PUBLIC museTimer
)

target_link_libraries(wheel_ut
        PUBLIC museTimer
)


add_test( NAME "tree_ut" COMMAND tree_ut )
add_test( NAME "wheel_ut" COMMAND wheel_ut )

