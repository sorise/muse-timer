cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

project(muse_timer
        VERSION         0.0.1
        DESCRIPTION     "timer wheel!"
        HOMEPAGE_URL    "https://github.com/sorise"
        LANGUAGES       C CXX
)

include_directories(include)
include_directories(dependency/catch2)
include_directories(dependency/concurrent_queue)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED  ON)

if (WIN32)
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
endif ()

add_library(museTimer SHARED
    include/timer/timer_wheel.cpp
    include/timer/timer_tree.cpp
    include/thread_pool/conf.cpp
    include/thread_pool/executor.cpp
    include/thread_pool/pool.cpp
    include/thread_pool/concurrent_pool.cpp
)

add_executable(runner main.cpp)

target_link_libraries(runner
    PUBLIC museTimer
)

# 启动单元测试
enable_testing()
# 进入单元测试

add_executable(tree_ut tests/treeTimer_ut.cpp)
add_executable(wheel_ut tests/wheelTimer_ut.cpp)

target_link_libraries(tree_ut
        PUBLIC museTimer
)

target_link_libraries(wheel_ut
        PUBLIC museTimer
)

add_test( NAME "tree_ut" COMMAND tree_ut )
add_test( NAME "wheel_ut" COMMAND wheel_ut )
