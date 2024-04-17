cmake_minimum_required(VERSION 3.10)
project(fem CXX)

find_package(OpenMP REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/src/include)
include_directories(/opt/openmpi/include)
# abmac_baseという名前のライブラリを作成し、
# それに含まれるソースファイルを指定する。
add_library(fem_base
    src/src-nompi/Node.cpp
    src/src-nompi/FileReader.cpp
    src/src-nompi/Logger.cpp
    src/src-nompi/State.cpp
    src/src-nompi/Params.cpp
    src/src-nompi/QuadElement.cpp
    src/src-nompi/TriElement.cpp
)

message(STATUS "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")


# 'main.cpp'というソースファイルを使用して、'main'という名前の
# 実行ファイルを作成する。
add_executable(main src/src-nompi/main.cpp)

# 'main'という実行可能ファイルに対して
# 先に定義した'fem_base'ライブラリをリンクする。
target_link_libraries(main fem_base)
