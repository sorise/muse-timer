cmake_minimum_required(VERSION 3.25)

project(muse_timer
        VERSION         0.0.1
        DESCRIPTION     "A Simple RPC Application Framework Based on Connection UDP"
        HOMEPAGE_URL    "https://github.com/sorise"
        LANGUAGES       C CXX
)

include_directories(include)
include_directories(dependency/catch2)
include_directories(dependency/concurrent_queue)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED  ON)

add_library(muse_timer SHARED
        include/timer/timer_wheel.cpp
        include/timer/timer_tree.cpp
        include/thread_pool/conf.cpp
        include/thread_pool/executor.cpp
        include/thread_pool/pool.cpp
        include/thread_pool/concurrent_pool.cpp
)

#add_executable(muse_timer main.cpp)

#target_link_libraries(muse_timer
#        PUBLIC timer muse_timer
#)

# 启动单元测试
enable_testing()
# 进入单元测试
add_subdirectory(tests)