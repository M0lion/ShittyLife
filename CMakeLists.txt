#c++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#includes
include(ExternalProject)

#beurocracy
cmake_minimum_required (VERSION 3.9)

#project
project(ShittyLife)

#includes
include_directories(${CMAKE_CURRENT_BINARY_DIR}/install/include)

#libs
link_directories(${CMAKE_CURRENT_BINARY_DIR}/install/lib)

#local cpps
file(GLOB SOURCES "src/*.cpp")

#exe
add_executable(ShittyLife ${SOURCES})

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

add_dependencies(ShittyLife glew)

if(UNIX)
set(GLEW_LIB libGLEW.a)
else()  
set(GLEW_LIB libglew32d.lib)
endif()

#glfw

if(UNIX)
  execute_process(COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/fuckGLFW.sh")

  add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/glfw)
  include_directories(${CMAKE_CURRENT_BINARY_DIR}/glfw/include)

  set(GLFW_LIB glfw ${GLFW_LIBRARIES})
else()
  ExternalProject_Add(glfw-external
    URL https://github.com/glfw/glfw/releases/download/3.2.1/glfw-3.2.1.zip
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/glfw
    INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/install
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
  )

  add_dependencies(ShittyLife glfw-external)
  set(GLFW_LIB ${install_dir}/lib/glfw3.lib)
endif()

#opengl
find_package(OpenGL REQUIRED)

#gml 
ExternalProject_Add(glm
  URL https://github.com/g-truc/glm/releases/download/0.9.8.5/glm-0.9.8.5.zip
  PREFIX ${CMAKE_CURRENT_BINARY_DIR}/glm
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ${CMAKE_COMMAND} -E copy_directory
                  <SOURCE_DIR>/glm ${CMAKE_BINARY_DIR}/install/include/glm
)
add_dependencies(ShittyLife glm)

set(LIBS ${GLEW_LIB} ${GLFW_LIB} ${OPENGL_gl_LIBRARY})
message(${LIBS})
target_link_libraries(ShittyLife  ${LIBS})