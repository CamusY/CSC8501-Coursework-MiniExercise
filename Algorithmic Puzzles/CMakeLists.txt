# 设置要求的 CMake 最低版本
cmake_minimum_required(VERSION 3.10)

# 设置项目名称
project(FirstPuzzleProject)

# 添加一个可执行文件
# 它的名字叫 FirstPuzzle，由 FirstPuzzle.cpp 文件编译而来
add_executable(FirstPuzzle FirstPuzzle.cpp)