# ============================================================
# C++ 项目模板（CMake + Ninja + GCC）
#
# 用法：把这个目录（含 .vscode）整个复制到你的项目根目录即可。
#   · 源文件：放根目录或 src/ 下 —— 会自动收集，加文件不用改本文件
#   · 头文件：放 include/
#   · 可执行文件名 = 文件夹名
# 工具位置不写死：cmake / ninja / g++ / gdb 都从 PATH 找。
# ============================================================
cmake_minimum_required(VERSION 3.20)

# 项目名自动取文件夹名，复制后不用改
get_filename_component(TPL_NAME "${CMAKE_CURRENT_SOURCE_DIR}" NAME)
string(REPLACE " " "_" TPL_NAME "${TPL_NAME}")
project(${TPL_NAME} LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)   # 用 -std=c++20 而不是 gnu++20，能提前发现用了 GCC 扩展的代码
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)   # 给 clangd 用的编译数据库

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "构建类型" FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
    Debug Release RelWithDebInfo MinSizeRel)
endif()

# 自动收集源文件：根目录的源文件（不递归，避免把 build/ 里的也算进来）+ src/ 下递归
file(GLOB ROOT_SOURCES
  "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/*.cc"
  "${CMAKE_CURRENT_SOURCE_DIR}/*.cxx" "${CMAKE_CURRENT_SOURCE_DIR}/*.c")
file(GLOB_RECURSE SRC_SOURCES CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cxx" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")
set(SOURCES ${ROOT_SOURCES} ${SRC_SOURCES})

if(NOT SOURCES)
  message(WARNING "没找到源文件。放一个 main.cpp（根目录或 src/ 下），再重新『配置 CMake』。")
  return()
endif()

add_executable(${TPL_NAME} ${SOURCES}
    src/Main.cpp
    src/Menu.cpp
    src/Interface.cpp
    src/Move.cpp
    src/Food.cpp
    src/Input.cpp)
target_include_directories(${TPL_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  target_compile_options(${TPL_NAME} PRIVATE
    -Wall -Wextra -Wpedantic
    -finput-charset=UTF-8 -fexec-charset=UTF-8)
elseif(MSVC)
  target_compile_options(${TPL_NAME} PRIVATE /W4 /utf-8)
endif()

message(STATUS "已收集源文件：" ${SOURCES})
