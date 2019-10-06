cmake_minimum_required(VERSION 3.10.1)
project(LosTopos)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set (Directories
 .
 common
 common/tunicate
 common/newsparse
 LosTopos3D
)

#FILE(GLOB_RECURSE Headers  RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/common *.h)
FILE(GLOB_RECURSE Headers  ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
FILE(GLOB_RECURSE Sources ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

find_package(BLAS REQUIRED)

add_library(LosTopos SHARED ${Headers} ${Sources})
target_include_directories(LosTopos PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries (LosTopos ${BLAS_LIBRARIES})


target_link_options(LosTopos PRIVATE ${BLAS_LINKER_FLAGS})
