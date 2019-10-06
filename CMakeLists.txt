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
find_package(LAPACK REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

message(STATUS "${OPENGL_FOUND}")
message(STATUS "${OPENGL_GLU_FOUND}")
message(STATUS "${OpenGL_OpenGL_FOUND}")
message(STATUS "${OPENGL_LIBRARIES}")

add_library(LosTopos SHARED ${Headers} ${Sources})
target_compile_definitions(LosTopos PUBLIC -DUSE_CBLAS)
target_include_directories(LosTopos PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${GLUT_INCLUDE_DIR})
target_link_libraries (LosTopos ${BLAS_LIBRARIES} ${LAPACK_LIBRARIES} OpenGL::GL OpenGL::GLU ${GLUT_LIBRARIES} cblas)
target_link_options(LosTopos PRIVATE ${BLAS_LINKER_FLAGS} ${LAPACK_LINKER_FLAGS})


