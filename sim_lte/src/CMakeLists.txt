include_directories("${PROJECT_SOURCE_DIR}/sim_lte/inc")
aux_source_directory(. DIR_SRCS)
add_library(sim_lte_lib ${DIR_SRCS})