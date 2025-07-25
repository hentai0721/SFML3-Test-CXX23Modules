cmake_minimum_required(VERSION 4.0.3)

set(CMAKE_CXX_MODULE_STD ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "d0edc3af-4c50-42ea-a356-e2862fe7a444")
set(CXX_SCAN_FOR_MODULES ON)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:DebugDLL>")
set(SFML_STATIC_LIBRARIES ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
#set(CMAKE_PREFIX_PATH "C:/Users/henta/Downloads/SFML-3.0.1")

project(HENTAI LANGUAGES CXX)

add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/source-charset:utf-8>)

add_executable(hentai WIN32)

add_library(libhentai SHARED)

target_sources(hentai
    PRIVATE
    src/main.cpp
)

target_sources(libhentai
    PUBLIC
    FILE_SET modules TYPE CXX_MODULES FILES
    modules/core/core.cppm 
    modules/core/core-concepts.cppm
    modules/core/core-coroutines.cppm 
    modules/core/core-math.cppm 
    modules/core/core-ui.cppm 
    modules/core/core-utils.cppm
    modules/sfml/sfml.cppm

    PRIVATE
    src/core/core.cpp
    src/core/core-utils.cpp
)


add_custom_target(run
    COMMAND $<TARGET_FILE:hentai>
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    DEPENDS hentai
)


set_target_properties(libhentai PROPERTIES PREFIX ""
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}"
)


set_target_properties(hentai PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}"
)

find_package(SFML 3 REQUIRED COMPONENTS System Window Graphics Audio Network Main)
target_link_libraries(libhentai PUBLIC SFML::System SFML::Window SFML::Graphics SFML::Audio SFML::Network SFML::Main)
target_link_libraries(hentai PRIVATE libhentai)
target_compile_options(libhentai PRIVATE $<$<AND:$<CONFIG:Release>,$<CXX_COMPILER_ID:Clang,MINGW,GNU>>:-fvisibility=hidden -Wall -Wextra -Wpedantic -Wreturn-type -Wconversion>)
target_compile_options(hentai PRIVATE $<$<AND:$<CONFIG:Release>,$<CXX_COMPILER_ID:Clang,MINGW,GNU>>:-Wall -Wextra -Wpedantic -Wreturn-type -Wconversion>)
target_compile_options(libhentai PRIVATE $<$<AND:$<CONFIG:Release>,$<CXX_COMPILER_ID:MSVC>>:/permissive- /W4>)
target_compile_options(hentai PRIVATE $<$<AND:$<CONFIG:Release>,$<CXX_COMPILER_ID:MSVC>>:/permissive- /W4>)
target_link_options(hentai PRIVATE $<$<AND:$<CONFIG:Release>,$<CXX_COMPILER_ID:Clang,MINGW,GNU>>:-s -static>)
target_link_options(libhentai PRIVATE $<$<AND:$<CONFIG:Release>,$<CXX_COMPILER_ID:Clang,MINGW,GNU>>:-s -static>)
target_link_options(hentai PRIVATE $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:Release>>:/OPT:REF /OPT:ICF /INCREMENTAL:NO>)
target_link_options(libhentai PRIVATE $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:Release>>:/OPT:REF /OPT:ICF /INCREMENTAL:NO>)