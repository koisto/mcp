cmake_minimum_required(VERSION 3.28)

project(mcp-hello)


add_executable(mcp-hello
    src/main.cpp
    src/json_rpc.cpp)

target_include_directories(mcp-hello PRIVATE third_party)




