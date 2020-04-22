cmake_minimum_required(VERSION 3.5)

aux_source_directory(. SRC_LIST)

add_executable(adaptor ${SRC_LIST})

target_link_libraries(adaptor python3.6m)
