cmake_minimum_required(VERSION 3.10.1)
project(LosTopos)
add_definitions(-DUSE_FORTRAN_BLAS)

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


find_package (OpenGL REQUIRED)

find_package (GLUT REQUIRED glut)

add_library(LosTopos SHARED ${Headers} ${Sources})
target_include_directories(LosTopos PRIVATE ${GLUT_INCLUDE_DIR})
target_include_directories(LosTopos PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries (LosTopos OpenGL::OpenGL ${GLUT_glut_LIBRARY})


