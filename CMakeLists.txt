cmake_minimum_required(VERSION 3.21)
project(lte_link_sim)
set(CMAKE_CXX_STANDARD 11)


# 头文件
include_directories("${PROJECT_SOURCE_DIR}/lib")
include_directories("${PROJECT_SOURCE_DIR}/sim_init/inc")
include_directories("${PROJECT_SOURCE_DIR}/sim_core/inc")
include_directories("${PROJECT_SOURCE_DIR}/sim_lte/inc")
include_directories("${PROJECT_SOURCE_DIR}/3rd/inc")

# 子目录
add_subdirectory("${PROJECT_SOURCE_DIR}/sim_init/src")
add_subdirectory("${PROJECT_SOURCE_DIR}/sim_core/src")
add_subdirectory("${PROJECT_SOURCE_DIR}/sim_lte/src")
add_subdirectory("${PROJECT_SOURCE_DIR}/3rd/src")

set(EXTRA_LIBS ${EXTRA_LIBS} sim_core_lib)
set(EXTRA_LIBS ${EXTRA_LIBS} sim_init_lib)
set(EXTRA_LIBS ${EXTRA_LIBS} sim_lte_lib)
set(EXTRA_LIBS ${EXTRA_LIBS} 3rd_lib)

# 选中源码库
aux_source_directory(test DIR_SRCS)

# main 函数
add_executable(lte_link_sim test/main.cpp )

# 链接库
target_link_libraries(${PROJECT_NAME} ${EXTRA_LIBS})
