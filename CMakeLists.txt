# 设置可以使用的最低 CMake 版本
cmake_minimum_required(VERSION 3.5)
# 设置项目名称
project(underpants)

# Enable C++20
set(CMAKE_CXX_STANDARD 20)

# 添加可执行文件
set(SRC_LIST
        source/utilities/logger.cpp
        source/utilities/logger.hpp
        source/utilities/file_controller.cpp
        source/utilities/file_controller.hpp
        source/game_management/game_controller.cpp
        source/game_management/game_controller.hpp
        source/utilities/types.cpp
        source/game_data/game_setting.cpp
        source/game_data/global_data_manager.cpp
        source/game_data/player_data.cpp
        source/game_place/lobby.cpp
        source/game_place/lobby.hpp
        source/game_management/console.cpp
        source/utilities/string_util.cpp
        source/utilities/string_util.hpp
        source/game_data/game_info.cpp
        source/game_data/game_info.hpp
        source/game_place/selection.cpp
        source/game_place/selection.hpp
        source/game_place/abstract_place.cpp
        source/game_place/abstract_place.hpp
        source/game_place/place_manager.cpp
        source/game_place/place_manager.hpp
)
aux_source_directory(./source/ SRC_LIST)
aux_source_directory(./lib/source/ SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})

# 添加头文件目录
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