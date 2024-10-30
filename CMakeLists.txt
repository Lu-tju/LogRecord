# 设置最低CMake版本
cmake_minimum_required(VERSION 3.10)

# 项目信息
project(LogRecordExample)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)

add_executable(LogRecordExample example.cpp logRecord.h)
