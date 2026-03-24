cmake_minimum_required(VERSION 3.10)
project(BoostExample)

find_package(Boost REQUIRED)

add_executable(myboostapp main.cpp)
target_include_directories(myboostapp PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(myboostapp PRIVATE uring)
