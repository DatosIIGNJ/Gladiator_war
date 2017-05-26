cmake_minimum_required(VERSION 3.6)
project(json)

set(CMAKE_CXX_STANDARD 11)

include_directories(usr/curl/include)
link_directories(usr/curl/lib)

set(game_LIBS libcurl.so)

set(SOURCE_FILES main.cpp)
add_executable(json ${SOURCE_FILES})

target_link_libraries(json ${game_LIBS})