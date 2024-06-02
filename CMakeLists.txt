cmake_minimum_required(VERSION 3.10)
project(fem CXX)

find_package(OpenMP REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/src/include)
include_directories(/opt/openmpi/include)
# fem_baseという名前のライブラリを作成し、
# それに含まれるソースファイルを指定する。
add_library(fem_base
    src/src-nompi/Node.cpp
    src/src-nompi/FileReader.cpp
    src/src-nompi/Logger.cpp
    src/src-nompi/State.cpp
    src/src-nompi/Params.cpp
    src/src-nompi/ElementTri.cpp
    src/src-nompi/ElementQuad.cpp
    src/src-nompi/ErrorMessage.cpp
    src/src-nompi/FileWriter.cpp
    src/src-nompi/FileReader.cpp
)

message(STATUS "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")


# 'main.cpp'というソースファイルを使用して、'main'という名前の
# 実行ファイルを作成する。
add_executable(main src/src-nompi/main.cpp)

# 'main'という実行可能ファイルに対して
# 先に定義した'fem_base'ライブラリをリンクする。
target_link_libraries(main fem_base)


add_library(fem_test_base
    src/test/TestBase.cpp
)

target_link_libraries(fem_test_base fem_base)

add_executable(test_Array src/test/test_Array.cpp)
target_link_libraries(test_Array fem_test_base)

add_executable(test_Matrix src/test/test_Matrix.cpp)
target_link_libraries(test_Matrix fem_test_base)

add_executable(test_State src/test/test_State.cpp)
target_link_libraries(test_State fem_test_base)

add_executable(test_ElementQuad src/test/test_ElementQuad.cpp)
target_link_libraries(test_ElementQuad fem_test_base)
