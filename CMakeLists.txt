#includes
include(ExternalProject)

#beurocracy
cmake_minimum_required (VERSION 2.6)

#project
project(ShittyTest)

#includes
include_directories(${CMAKE_CURRENT_BINARY_DIR}/install/include)

#libs
link_directories(${CMAKE_CURRENT_BINARY_DIR}/install/lib)

#local cpps
file(GLOB SOURCES "src/*.cpp")

#exe
add_executable(ShittyGL ${SOURCES})

#meme
set(install_dir ${CMAKE_CURRENT_BINARY_DIR}/install)

#glew

ExternalProject_Add(glew
  URL https://sourceforge.net/projects/glew/files/glew/2.1.0/glew-2.1.0.zip/download
  PREFIX ${CMAKE_CURRENT_BINARY_DIR}/glew
  INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/install
  SOURCE_SUBDIR build/cmake
  CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
)

if(UNIX)
set(GLEW_LIB glew32d.a)
else()
set(GLEW_LIB glew32d.lib)
endif()

#glfw
ExternalProject_Add(glfw-external
  URL https://github.com/glfw/glfw/releases/download/3.2.1/glfw-3.2.1.zip
  PREFIX ${CMAKE_CURRENT_BINARY_DIR}/glfw
  INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/install
  CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
)
if(UNIX)
  set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
  set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
  set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
  add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/glfw/src/glfw)
  
  set(GLFW_LIB glfw)
else()
  set(GLFW_LIB ${install_dir}/lib/glfw3.lib)
endif()

#opengl
find_package(OpenGL REQUIRED)

target_link_libraries(ShittyGL  ${GLEW_LIB} ${GLFW_LIB} ${OPENGL_gl_LIBRARY})