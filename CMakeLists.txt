cmake_minimum_required (VERSION 2.6)
project (tinyjson)

aux_source_directory(src SRC_LIST)

add_executable(tinyjson ${SRC_LIST})