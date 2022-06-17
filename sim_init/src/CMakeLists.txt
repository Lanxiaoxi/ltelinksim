include_directories("${PROJECT_SOURCE_DIR}/sim_init/inc")
aux_source_directory(. DIR_SRCS)
add_library(sim_init_lib ${DIR_SRCS})