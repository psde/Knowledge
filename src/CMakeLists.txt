# global definitions
set(LOCAL_EXTRA_C_FLAGS "")


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

set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib CACHE PATH "Output directory for libraries" )
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin CACHE PATH "Output directory for applications" )

# core
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/core")