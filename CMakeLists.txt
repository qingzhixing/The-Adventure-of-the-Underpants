# 设置可以使用的最低 CMake 版本
cmake_minimum_required(VERSION 3.5)
# 设置项目名称
project (underpants)
# 添加可执行文件
add_executable(underpants ./source/main.cpp)
# 添加头文件目录
# target_include_directories(underpants PRIVATE ./include)

# # 批量添加源文件
# file(GLOB SRCS CONFIGURE_DEPENDS ./src/*.cpp)
# target_sources(underpants PUBLIC ${SRCS})
# # 添加第三方库
# find_package(OpenGL CONFIG REQUIRED)
# # 链接第三方库
# target_link_libraries(underpants PRIVATE OpenGL)
# # 指定输出路径
# set_property(TARGET underpants ${CMAKE_SOURCE_DIR}/bin)