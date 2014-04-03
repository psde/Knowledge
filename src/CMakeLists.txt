# include this directory
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# core
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/core")

# core-test
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/core-test")

# opencv-test
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/opencv-test")

# portAudio
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/portAudio")

# portAudio-test
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/portAudio-test")
