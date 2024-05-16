# 设置可以使用的最低 CMake 版本
cmake_minimum_required(VERSION 3.5)
# 设置项目名称
project(underpants)
# 添加可执行文件
# set(SRC_LIST 
#     ./source/main.cpp
#     )
aux_source_directory(./source/ SRC_LIST)
aux_source_directory(./lib/source/ SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST}
        source/logger.cpp
        include/logger.hpp
        include/file_controller.cpp
        include/file_controller.hpp)

# 添加头文件目录
target_include_directories(${PROJECT_NAME} PRIVATE ./include)
target_include_directories(${PROJECT_NAME} PRIVATE ./lib/include)

# # 批量添加源文件
# file(GLOB SRCS CONFIGURE_DEPENDS ./src/*.cpp)
# target_sources(${PROJECT_NAME} PUBLIC ${SRCS})
# # 添加第三方库
# find_package(OpenGL CONFIG REQUIRED)
# # 链接第三方库
# target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL)
# # 指定输出路径
# set_property(TARGET ${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/bin)