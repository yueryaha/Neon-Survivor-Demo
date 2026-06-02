cmake_minimum_required(VERSION 3.14)
project(NeonSurvivor)

# 设置 C++ 标准为 C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 告诉 CMake 自动去下载 Raylib 5.0 版本
include(FetchContent)
FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/refs/tags/5.0.tar.gz
)
FetchContent_MakeAvailable(raylib)

# 将你的 cpp 文件编译成可执行文件
add_executable(NeonSurvivor 
    main.cpp 
    player.cpp 
    enemy.cpp 
    bullet.cpp
)

# 强制 MSVC 编译器使用 UTF-8 编码读取源文件，防止中文注释引发编译错误
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

# 链接 Raylib 库
target_link_libraries(NeonSurvivor PRIVATE raylib)