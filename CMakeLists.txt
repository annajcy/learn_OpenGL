cmake_minimum_required(VERSION 3.27)
project(learn_opengl)

set(CMAKE_CXX_STANDARD 20)

add_definitions(-DDEBUG)

file(GLOB ASSETS "assets" )
file(COPY ${ASSETS} DESTINATION ${CMAKE_BINARY_DIR})

set(GLAD_PATH ${CMAKE_SOURCE_DIR}/third_party/glad)
set(GLFW_PATH ${CMAKE_SOURCE_DIR}/third_party/glfw)
set(GLM_PATH ${CMAKE_SOURCE_DIR}/third_party/glm)
set(STB_IMAGE_PATH ${CMAKE_SOURCE_DIR}/third_party/stb_image)

file(GLOB_RECURSE GLOBAL_SRC ${CMAKE_SOURCE_DIR}/global/*.cpp)
file(GLOB_RECURSE APPLICATION_SRC ${CMAKE_SOURCE_DIR}/application/*.cpp)
file(GLOB_RECURSE GRAPHICS_SRC ${CMAKE_SOURCE_DIR}/graphics/*.cpp)

find_package(OpenGL REQUIRED)
if (NOT OpenGL_FOUND)
    message(FATAL_ERROR "OpenGL not found!")
endif()

include_directories(
    ${CMAKE_SOURCE_DIR}
    ${OPENGL_INCLUDE_DIR}
)

include_directories(
    ${GLAD_PATH}/include
	${GLFW_PATH}/include
    ${STB_IMAGE_PATH}/include
    ${GLM_PATH}/include
)

add_library(glm IMPORTED STATIC)
set_target_properties(glm PROPERTIES IMPORTED_LOCATION ${GLM_PATH}/lib64/libglm.a)

set(SOURCES
    ${APPLICATION_SRC}
    ${GRAPHICS_SRC}
    ${GLOBAL_SRC}
    ${GLAD_PATH}/src/glad.c
	${CMAKE_SOURCE_DIR}/main.cpp 
)

# 定义可执行目标
add_executable(learn_opengl ${SOURCES})

target_link_libraries(learn_opengl 
glfw 
glm
${OPENGL_LIBRARIES} 
)
     
    