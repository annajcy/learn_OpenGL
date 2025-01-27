cmake_minimum_required(VERSION 3.27)
project(learn_opengl)

set(CMAKE_CXX_STANDARD 20)

# 定义宏 DEBUG
add_definitions(-DDEBUG)

# 包含头文件路径
include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/include
)

# 设置库文件路径
link_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/lib/assimp
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/lib/GLFW
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/lib/glm
)

# 获取 ThirdParty/Source/ 中的所有源文件
file(GLOB THIRD_PARTY_SRC_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/src/*.c
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/src/*.cpp
)

add_subdirectory(application)
add_subdirectory(error_check)

# 定义可执行目标
add_executable(learn_opengl
        main.cpp
        ${THIRD_PARTY_SRC_FILES}
)

# macOS 链接特定框架和库
if(APPLE)

    file(GLOB assimp_lib ${CMAKE_CURRENT_SOURCE_DIR}/third_party/lib/assimp/*.dylib)

    target_link_libraries(learn_opengl
            "-framework Cocoa"
            "-framework IOKit"
            "-framework CoreFoundation"
            "-framework CoreGraphics"
    )

    target_link_libraries(learn_opengl
            libglfw3.a
            libglm.a
            ${assimp_lib}
    )

endif()

target_link_libraries(learn_opengl
        application_lib
        error_check_lib
)
