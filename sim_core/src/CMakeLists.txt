include_directories("${PROJECT_SOURCE_DIR}/sim_core/inc")
aux_source_directory(. DIR_SRCS)
add_library(sim_core_lib ${DIR_SRCS})