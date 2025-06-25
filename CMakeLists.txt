cmake_minimum_required(VERSION 4.0.2)

set(CMAKE_CXX_MODULE_STD ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "a9e1cf81-9932-4810-974b-6eccaf14e457")
set(CXX_SCAN_FOR_MODULES ON)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:DebugDLL>")
#set(SFML_DIR "C:/Users/henta/Downloads/SFML-3.0.1/lib/cmake/SFML")
#set(CMAKE_PREFIX_PATH "C:/Users/henta/Downloads/SFML-3.0.1")
set(SFML_STATIC_LIBRARIES ON)

project(HENTAI LANGUAGES CXX)

add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/source-charset:utf-8>)

add_executable(hentai WIN32)

target_sources(hentai
    PUBLIC
    FILE_SET modules TYPE CXX_MODULES FILES
    sfml.cppm Core.cppm
    PRIVATE
    Core.cpp main.cpp
)

add_custom_target(run
    COMMAND hentai
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    DEPENDS hentai
)

find_package(SFML 3 REQUIRED COMPONENTS System Window Graphics Audio Network Main)
target_link_libraries(hentai PRIVATE SFML::System SFML::Window SFML::Graphics SFML::Audio SFML::Network SFML::Main)
target_link_options(hentai PRIVATE $<$<AND:$<CONFIG:Release>,$<CXX_COMPILER_ID:Clang,MINGW,GNU>>:-s -static>)
#target_compile_definitions