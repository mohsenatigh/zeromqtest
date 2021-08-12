cmake_minimum_required (VERSION 2.6)
project(mqtest)


#regenrate messages
execute_process (
    COMMAND bash -c "../rpc/generate.sh"
    WORKING_DIRECTORY "../rpc/"
)

cmake_minimum_required (VERSION 2.6)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")


add_subdirectory(client)
add_subdirectory(server)
