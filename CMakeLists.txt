cmake_minimum_required(VERSION 3.27)
project(learn_opengl)

set(CMAKE_CXX_STANDARD 20)

add_definitions(-DDEBUG)

file(GLOB ASSETS "./assets" )
file(COPY ${ASSETS} DESTINATION ${CMAKE_BINARY_DIR})

set(GLAD_PATH ${CMAKE_SOURCE_DIR}/third_party/glad)
set(GLFW_PATH ${CMAKE_SOURCE_DIR}/third_party/glfw)

file(GLOB_RECURSE APPLICATION_SRC ${CMAKE_SOURCE_DIR}/application/*.cpp)
file(GLOB_RECURSE ERROR_CHECK_SRC ${CMAKE_SOURCE_DIR}/error_check/*.cpp)
file(GLOB_RECURSE SHADER_SRC ${CMAKE_SOURCE_DIR}/shader/*.cpp)

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
)

set(SOURCES

    ${APPLICATION_SRC}
    ${ERROR_CHECK_SRC}
    ${SHADER_SRC}

    ${GLAD_PATH}/src/glad.c

	${CMAKE_SOURCE_DIR}/main.cpp 
)

# 定义可执行目标
add_executable(learn_opengl ${SOURCES})

target_link_libraries(learn_opengl glfw ${OPENGL_LIBRARIES} )
     
    