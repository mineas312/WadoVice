cmake_minimum_required(VERSION 3.9)

# Project variables
set(PROJECT_NAME "WadoVice")
set(PROJECT_VERSION "1.0")

# Language standard
set(CMAKE_CXX_STANDARD 17)

# Enable debug symbols
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# ---- Shared library project ----
project(${PROJECT_NAME} VERSION ${PROJECT_VERSION} DESCRIPTION "Changeme")

# Disable MSVC warnings
add_definitions(-_CRT_SECURE_NO_WARNINGS)

# Add DirectX
include_directories($ENV{DXSDK_DIR}/Include)
link_directories($ENV{DXSDK_DIR}/Lib/x64)

# Add include, src and resources to the project
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/src)
file(GLOB SRC_LIB_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/Drawing/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/Drawing/Anims/*.cpp)
file(GLOB RES_LIB_FILES ${CMAKE_CURRENT_SOURCE_DIR}/res/*.rc)

# Set project as a shared library
add_library(${PROJECT_NAME} SHARED ${SRC_LIB_FILES} ${RES_LIB_FILES})

# Set lib.so properties
set_target_properties(${PROJECT_NAME}
PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION}
)


# Compiler settings
if(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
    target_compile_options(${PROJECT_NAME} PRIVATE /EHsc /MTd /W2 /c)
    target_compile_definitions(${PROJECT_NAME} PRIVATE WIN_EXPORT)
endif()


# ---- Executable project ----
project("TestExe" VERSION ${PROJECT_VERSION} DESCRIPTION "Changeme")

# Add src to the project
file(GLOB SRC_EXE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/exe/src/*.cpp)

add_executable("TestExe" WIN32 ${SRC_EXE_FILES})

# Add include to the project
target_include_directories("TestExe" PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/exe/include ${CMAKE_CURRENT_SOURCE_DIR}/exe/src)

target_link_libraries("TestExe" "WadoVice")

SET_TARGET_PROPERTIES("TestExe" PROPERTIES LINK_FLAGS "/MANIFESTUAC:\"level='requireAdministrator' uiAccess='false'\" /SUBSYSTEM:WINDOWS")

# Injector project
project("WadoVice_Injector" VERSION "1.0")

# Disable MSVC warnings
add_definitions(-_CRT_SECURE_NO_WARNINGS)

add_executable("WadoVice_Injector" injector/main.cpp)

SET_TARGET_PROPERTIES("WadoVice_Injector" PROPERTIES LINK_FLAGS "/MANIFESTUAC:\"level='requireAdministrator' uiAccess='false'\" /SUBSYSTEM:WINDOWS")
