file(GLOB lib_source "source/*.cpp" "source/*.c")
file(GLOB lib_headers "include/*.h")

file(GLOB lib_os_source "source/${cpplibtemplate_os}/*.cpp" "source/${cpplibtemplate_os}/*.c")
file(GLOB lib_os_headers "include/${cpplibtemplate_os}/*.h")

add_library(mylib STATIC ${lib_source} ${lib_headers} ${lib_os_source} ${lib_os_headers})

target_include_directories(mylib PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/>
    $<INSTALL_INTERFACE:include/>)

target_link_libraries(mylib PUBLIC )

target_compile_features(mylib PUBLIC cxx_std_98)

# Disable "Security" warnings
if(WIN32)
    target_compile_definitions(mylib PUBLIC _CRT_SECURE_NO_WARNINGS)
endif()

# Disable RTTI and Exceptions
if(MSVC)
    target_compile_options(mylib PUBLIC /GR-)
else()
    target_compile_options(mylib PUBLIC -fno-rtti -fno-exceptions)
endif()

# Warnings as errors
if(MSVC)
    target_compile_options(mylib PRIVATE /W4 /WX)
else()
    target_compile_options(mylib PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

install(TARGETS mylib
        EXPORT cpplibtemplate-config
        LIBRARY DESTINATION lib/${install_destination}
        ARCHIVE DESTINATION lib/${install_destination})

install(FILES ${lib_headers}
        DESTINATION include/)