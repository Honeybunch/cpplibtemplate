
file(GLOB lib_source "source/*.cpp" "source/*.c")
file(GLOB lib_headers "include/*.h")

file(GLOB lib_os_source "source/${cpplibtemplate_os}/*.cpp" "source/${cpplibtemplate_os}/*.c")
file(GLOB lib_os_headers "include/${cpplibtemplate_os}/*.h")

add_library(examplecore STATIC ${lib_source} ${lib_headers} ${lib_os_source} ${lib_os_headers})

target_link_libraries(examplecore PUBLIC mylib)
target_include_directories(examplecore PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)