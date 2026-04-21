# Ruka Raposa Project by Ruka Raposa Team & Contribuitors.
# Project is under GPL3-license, read LICENSE.md on the root.
cmake_minimum_required(VERSION 3.20)
project(
    3xJson
    VERSION 1.0.000
)

# Set the options:
option(XJ_ENABLE_ASAN "If you want to enable ASan" OFF)
option(XJ_STATIC "Build 3xjson static" ON)
option(XJ_SHARED "Build 3xjson shared" OFF)
option(XJ_TESTS "Build the tests" OFF)
option(XJ_VENDOR_NAME "Sets the vendor information" "Ruka Raposa")
option(XJ_SELF_BUILD "This defines if you are just testing" OFF)

# Are we just testing? 
# This will automatically (should) the NK project.
if(XJ_SELF_BUILD)
    message(STATUS "Adding NK from TD/NK [trying ...]")
    add_subdirectory(TD/NK)
endif()

# Set the functions
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake")
include(XJ_ASanSupport)
include(XJ_TryToAddLibrary)

# Build the target:
add_library(XJ_Headers INTERFACE)
target_include_directories(XJ_Headers INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include")

# Glob the files:
file(GLOB_RECURSE xj_sources "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")

# Create the dependencies:
add_library(XJ_Libraries INTERFACE)
cmake_language(CALL XJ_TryAddToLibrary NK::NK-static XJ_Libraries)

# Static Target:
if(XJ_STATIC OR XJ_TESTS)
    add_library(XJ_Static STATIC ${xj_sources})
    target_link_libraries(XJ_Static PUBLIC XJ_Headers)
    target_link_libraries(XJ_Static PRIVATE XJ_ASanSupportInterface)
    target_link_libraries(XJ_Static PRIVATE XJ_Libraries)
    add_library(XJ::XJ-static ALIAS XJ_Static)
endif()

# Shared Target:
if(XJ_SHARED)
    add_library(XJ_Shared ${xj_sources})
    target_link_libraries(XJ_Shared PUBLIC XJ_Headers)
    target_link_libraries(XJ_Shared PRIVATE XJ_ASanSupportInterface)
    target_link_libraries(XJ_Shared PRIVATE XJ_Libraries)
    add_library(XJ::XJ-shared ALIAS XJ_Shared)
endif()

# Tests:
if(XJ_TESTS)
    include(XJ_GenerateTests)
    add_library(XJ_TestsInterface INTERFACE)
    target_link_libraries(XJ_TestsInterface INTERFACE XJ_Static)
    target_link_libraries(XJ_TestsInterface INTERFACE XJ_ASanSupportInterface)
    target_link_libraries(XJ_TestsInterface INTERFACE XJ_Libraries)
    set(xj_tests
        "${CMAKE_CURRENT_SOURCE_DIR}/tests/XJDecoderTokenizerTest.c" "XJDecoderTokenizerTest"
    )
    cmake_language(CALL XJ_GenerateTests "${xj_tests}" XJ_TestsInterface)
endif()

# Message:
message(STATUS "[[ 3xjson \"${XJ_VENDOR_NAME}\" - Version: ${PROJECT_VERSION} ]]")
message(STATUS "Enable Static: ${XJ_STATIC}")
message(STATUS "Enable Shared: ${XJ_SHARED}")
message(STATUS "Enable ASan: ${XJ_ENABLE_ASAN}")
message(STATUS "Enable Tests: ${XJ_TESTS}")
message(STATUS "[[ 3xjson \"${XJ_VENDOR_NAME}\" - Version: ${PROJECT_VERSION} ]]")