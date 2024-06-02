cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

project(muse_timer
        VERSION         0.0.1
        DESCRIPTION     "timer wheel!"
        HOMEPAGE_URL    "git@github.com:sorise/muse-timer.git"
        LANGUAGES       C CXX
)

include_directories(include)
include_directories(dependency/catch2)
include_directories(dependency/concurrent_queue)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED  ON)
set(CMAKE_BUILD_TYPE "Release")

if (WIN32)
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
endif ()

set(INSTALL_PROGRAM_NAME "museTimer")

add_library(${INSTALL_PROGRAM_NAME} SHARED
        include/museTimer/timer/timer_wheel.cpp
        include/museTimer/timer/timer_tree.cpp
        include/museTimer/thread_pool/conf.cpp
        include/museTimer/thread_pool/executor.cpp
        include/museTimer/thread_pool/pool.cpp
        include/museTimer/thread_pool/concurrent_pool.cpp
)

option(OPEN_UINT_TEST "uint test need?" ON)

if (OPEN_UINT_TEST)
    #启动单元测试
    enable_testing()
    add_executable(tree_ut tests/treeTimer_ut.cpp)
    add_executable(wheel_ut tests/wheelTimer_ut.cpp)
    target_link_libraries(tree_ut
        PUBLIC ${INSTALL_PROGRAM_NAME}
    )
    target_link_libraries(wheel_ut
        PUBLIC ${INSTALL_PROGRAM_NAME}
    )
    add_test( NAME "tree_ut" COMMAND tree_ut )
    add_test( NAME "wheel_ut" COMMAND wheel_ut )
endif ()

# 指定安装目录
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    SET(CMAKE_INSTALL_PREFIX "C:/Program Files/${INSTALL_PROGRAM_NAME}")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    SET(CMAKE_INSTALL_PREFIX "/usr/local")
else(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    SET(CMAKE_INSTALL_PREFIX "/usr/local")
endif ()

MESSAGE(STATUS "PREFIX ${CMAKE_INSTALL_PREFIX}")

file(GLOB HEADER_FILES_POOL "include/museTimer/thread_pool/*.hpp" "include/museTimer/thread_pool/*.h")
file(GLOB HEADER_FILES_TIMER "include/museTimer/timer/*.hpp" "include/museTimer/timer/*.h" )
file(GLOB HEADER_Concurrent_Queue "dependency/concurrent_queue/*.h" )

# 安装头文件
install(FILES ${HEADER_FILES_POOL} DESTINATION "include/${INSTALL_PROGRAM_NAME}/thread_pool")
install(FILES ${HEADER_FILES_TIMER} DESTINATION "include/${INSTALL_PROGRAM_NAME}/timer")
install(FILES ${HEADER_Concurrent_Queue} DESTINATION "include/${INSTALL_PROGRAM_NAME}/thread_pool")
#安装目标
install(TARGETS ${INSTALL_PROGRAM_NAME} DESTINATION lib)