file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)

add_library (Stream INTERFACE)
target_include_directories (Stream INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})