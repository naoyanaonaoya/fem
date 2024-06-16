cmake_minimum_required(VERSION 3.10)
project(fem CXX)

add_custom_target(print_source_dir ALL
    COMMAND ${CMAKE_COMMAND} -E echo "CMAKE_SOURCE_DIR         : ${CMAKE_SOURCE_DIR}"
    COMMAND ${CMAKE_COMMAND} -E echo "CMAKE_BINARY_DIR         : ${CMAKE_BINARY_DIR}"
    COMMAND ${CMAKE_COMMAND} -E echo "CMAKE_BUILD_TYPE         : ${CMAKE_BUILD_TYPE}"
    COMMAND ${CMAKE_COMMAND} -E echo "CMAKE_CXX_COMPILER       : ${CMAKE_CXX_COMPILER}"
    COMMAND ${CMAKE_COMMAND} -E echo "CMAKE_CXX_FLAGS          : ${CMAKE_CXX_FLAGS}"
    COMMAND ${CMAKE_COMMAND} -E echo "CMAKE_INSTALL_PREFIX     : ${CMAKE_INSTALL_PREFIX}"
    COMMAND ${CMAKE_COMMAND} -E echo "CMAKE_INSTALL_BINDIR     : ${CMAKE_INSTALL_BINDIR}"
    COMMAND ${CMAKE_COMMAND} -E echo "CMAKE_INSTALL_LIBDIR     : ${CMAKE_INSTALL_LIBDIR}"
    COMMAND ${CMAKE_COMMAND} -E echo "CMAKE_INSTALL_INCLUDEDIR : ${CMAKE_INSTALL_INCLUDEDIR}"
    COMMAND ${CMAKE_COMMAND} -E echo "CMAKE_MODULE_PATH        : ${CMAKE_MODULE_PATH}"
    COMMAND ${CMAKE_COMMAND} -E echo "CMAKE_PREFIX_PATH        : ${CMAKE_PREFIX_PATH}"
    COMMAND ${CMAKE_COMMAND} -E echo "CMAKE_VERBOSE_MAKEFILE   : ${CMAKE_VERBOSE_MAKEFILE}"
)

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
    src/src-nompi/CfdDriver_sp.cpp
    src/src-nompi/CfdProcData.cpp
    src/src-nompi/CfdCommData.cpp
    src/src-nompi/ElementTri.cpp
    src/src-nompi/ElementQuad.cpp
    src/src-nompi/ErrorMessage.cpp
    src/src-nompi/FileWriter.cpp
    src/src-nompi/FileReader.cpp
    src/src-nompi/Boundary.cpp
    src/src-nompi/test.cpp
)

add_definitions(-DDEBUG_CFDPROCDATA)
add_definitions(-DDEBUG_FILEWRITER)


# 'main.cpp'というソースファイルを使用して、'main'という名前の
# 実行ファイルを作成する。
add_executable(main src/src-nompi/main.cpp)

# 'main'という実行可能ファイルに対して
# 先に定義した'fem_base'ライブラリをリンクする。
target_link_libraries(main fem_base)

add_executable(test src/src-nompi/test.cpp)

add_executable(gmsh2sdpss src/utility/gmsh2sdpss.cpp)


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

add_executable(test_Node src/test/test_Node.cpp)
target_link_libraries(test_Node fem_test_base)

add_executable(test_ElementQuad src/test/test_ElementQuad.cpp)
target_link_libraries(test_ElementQuad fem_test_base)

add_executable(test_Params src/test/test_Params.cpp)
target_link_libraries(test_Params fem_test_base)

add_executable(test_Boundary src/test/test_Boundary.cpp)
target_link_libraries(test_Boundary fem_test_base)
