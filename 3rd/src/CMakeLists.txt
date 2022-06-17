include_directories("${PROJECT_SOURCE_DIR}/3rd/inc")
aux_source_directory(. DIR_SRCS)
add_library(3rd_lib ${DIR_SRCS})