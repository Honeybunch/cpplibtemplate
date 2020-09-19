file(GLOB source "source/*.cpp" "source/*.c")
file(GLOB headers "source/*.h")

file(GLOB os_source "source/${cpplibtemplate_os}/*.cpp" "source/${cpplibtemplate_os}/*.c")
file(GLOB os_headers "source/${cpplibtemplate_os}/*.h")

add_executable(exampleone ${source} ${headers} ${os_source} ${os_headers})

target_link_libraries(exampleone PUBLIC examplecore)

install(TARGETS exampleone
        EXPORT mylib-config
        RUNTIME DESTINATION bin/${install_destination})