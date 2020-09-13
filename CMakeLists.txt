cmake_minimum_required(VERSION 3.13)
project(caerun CXX)

find_package(Threads)

set(CMAKE_CXX_STANDARD 17)

file(GLOB NSOCK_FILES ${PROJECT_SOURCE_DIR}/src/nsock/*.cpp)
file(GLOB NETSYSTEM_FILES ${PROJECT_SOURCE_DIR}/src/net/*.cpp)

set(
    SOURCE_FILES

    ${NSOCK_FILES}
    ${NETSYSTEM_FILES}
    src/main.cpp
)

add_executable(caerun ${SOURCE_FILES})

target_include_directories(caerun PUBLIC ${PROJECT_SOURCE_DIR}/src/)
target_link_libraries(caerun ${CMAKE_THREAD_LIBS_INIT})