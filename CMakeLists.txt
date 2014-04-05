project(Knowledge)
cmake_minimum_required(VERSION 2.8.12)

# Automatically link Qt executables to qtmain target on Windows.
# cmake --help-policy CMP0020
cmake_policy(SET CMP0020 NEW) 

set(APPLICATION_VERSION "0.0.1")
set(APPLICATION_NAME ${PROJECT_NAME})

# User config
include("UserDefinitions.cmake" OPTIONAL)

# Include custom functions/modules?
include("CMakeModules/FindQt5Module.cmake" REQUIRED)
include("CMakeModules/ConfigureCopyScript.cmake" REQUIRED)

# global definitions
set(LOCAL_EXTRA_C_FLAGS "")

# OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# Qt4
set(CMAKE_PREFIX_PATH "${Qt_ROOT};${CMAKE_PREFIX_PATH}")
find_package(Qt4 REQUIRED COMPONENTS QtCore QtGUI)
include_directories(${Qt_INCLUDE_DIRS})
add_definitions("${QT_DEFINITIONS}")

# pthreads
find_package(Threads)

# Compiler stuff
message(STATUS "-+---------------------------------------------")
if(CMAKE_COMPILER_IS_GNUCXX)
    message(STATUS " | Detected GNUCXX")
    set(LOCAL_EXTRA_C_FLAGS "${LOCAL_EXTRA_C_FLAGS} -Wall -Wextra -std=c++11 -pedantic -g")
elseif(MSVC)
    message(STATUS " | Detected MSVC")
    add_definitions("-D_CRT_SECURE_NO_WARNINGS")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    message(STATUS " | Detected Clang++")
    set(LOCAL_EXTRA_C_FLAGS "${LOCAL_EXTRA_C_FLAGS} -Wall -Wextra -Wno-c++98-compat -std=c++11 -pedantic")
else()
    message(STATUS " | Unknown Compiler")
endif()

message(STATUS " | compiler flags: ${LOCAL_EXTRA_C_FLAGS} ${EXTRA_C_FLAGS}")
message(STATUS "-+---------------------------------------------")
add_definitions("${LOCAL_EXTRA_C_FLAGS}")

# Set output paths
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib CACHE PATH "Output directory for libraries" )
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin CACHE PATH "Output directory for applications" )

# sources
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src")

if(WIN32)
  file(TO_NATIVE_PATH "${_OpenCV_LIB_PATH}" ENV_EXPORT_OpenCV_PATH)
  file(TO_NATIVE_PATH "${QT_BINARY_DIR}" ENV_EXPORT_Qt_PATH)
  file(TO_NATIVE_PATH "${CMAKE_BINARY_DIR}/lib" ENV_EXPORT_LIB_PATH)
  file(TO_NATIVE_PATH "${CMAKE_BINARY_DIR}/bin" ENV_EXPORT_BIN_PATH)

  configure_file("${PROJECT_SOURCE_DIR}/script/env.bat.in" "${CMAKE_BINARY_DIR}/env.bat")

  ConfigureCopyScript("OpenCV" "opencv" "*d.dll" "${ENV_EXPORT_OpenCV_PATH}")
  ConfigureCopyScript("Qt" "qt" "*d4.dll" "${ENV_EXPORT_Qt_PATH}")
endif()
