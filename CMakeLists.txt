cmake_minimum_required(VERSION 3.17)

project(cpplibtemplate)

# Disable /GR by default, can be forced on manually later
if(MSVC)
    string(REPLACE "/GR" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
    string(REPLACE "/GR" "" CMAKE_C_FLAGS ${CMAKE_C_FLAGS})
endif()

# Setup clang-tidy checks
set(clang_tidy_checks "*,-abseil-*,-boost-use-to-string,-cert-*,-bugprone-argument-comment,-cppcoreguidelines-*,cppcoreguidelines-pro-type-union-access,-darwin-*,-fuchsia-*,fuchsia-multiple-inheritance,fuchsia-statically-constructed-objects,fuchsia-trailing-return,fuchsia-virtual-inheritance,-google-*,google-runtime-int,google-runtime-operator,google-runtime-reference,-hicpp-*,hicpp-multiway-paths-covered,-llvm-*,llvm-namepsace-comment,-misc-uniqueptr-reset-release,-modernize-*,modenize-concat-nexted-namepsaces,modernize-use-emplace,modernize-use-override,modernize-use-using,-mpi-*m-open-mp*,-portability-simd-intrinsics,-readability-*,-zircon-temporary-objects")
set(clang_tidy_args clang-tidy;-header-filter=.*,-*vulkan*;-checks=${clang_tidy_checks};-warnings-as-errors=*;)

if(EXISTS clang-tidy)
    set(CMAKE_C_CLANG_TIDY ${clang_tidy_args})
    set(CMAKE_CXX_CLANG_TIDY ${clang_tidy_args})
endif()

if(WIN32)
    set(cpplibtemplate_os "windows")
else()
    message(FATAL_ERROR "Unsupported Platform")
endif()

# Decide which compiler wer're using and do any per-compiler logic
if(MSVC)
    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        set(cpplibtemplate_compiler "llvm")
    else()
        set(cpplibtemplate_compiler "msvc")
    endif()
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(cpplibtemplate_compiler "llvm")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    set(cpplibtemplate_compiler "gcc")
else()
    message(FATAL_ERROR "Unknown Compiler")
endif()

# Detect which generator is being used
if(CMAKE_GENERATOR MATCHES "Ninja")
    set(cpplibtemplate_generator "ninja")
elseif(CMAKE_GENERATOR MATCHES "Visual Studio 16 2019")
    set(cpplibtemplate_generator "vs2019")
elseif(CMAKE_GENERATOR MATCHES "Xcode")
    set(cpplibtemplate_generator "xcode")
else()
    set(cpplibtemplate_generator "unknown")
    message("Unknown build generator")
endif()

# Set install prefix if not already overridden
set(cpplibtemplate_install "${CMAKE_CURRENT_SOURCE_DIR}/cpplibtemplate/${cpplibtemplate_os}/${cpplibtemplate_generator}/${cpplibtemplate_compiler}/${cpplibtemplate_config}")
if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set (CMAKE_INSTALL_PREFIX ${cpplibtemplate_install} CACHE PATH "Default Install Path" FORCE )
else()
    set(cpplibtemplate_install ${CMAKE_INSTALL_PREFIX})
endif()

set(install_destination "$<LOWER_CASE:$<CONFIG>>")

add_subdirectory(examples)
add_subdirectory(lib)

install(EXPORT cpplibtemplate-config
        DESTINATION cmake/)