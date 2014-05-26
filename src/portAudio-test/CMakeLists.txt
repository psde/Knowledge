set(portAudio_TEST_SRCS
	main.cpp
	sine.cpp
	record.cpp
        SoundBuffer.cpp
        ../opencv-graph/Graph.cpp
)

set(portAudio_TEST_HDRS
	sine.h
	record.h
	split.h
        SoundBuffer.h
        ../opencv-graph/Graph.h
)
if(CMAKE_COMPILER_IS_GNUCXX)
    message(STATUS " | Detected GNUCXX")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++11 -pedantic -g")
endif()

find_package(OpenCV REQUIRED)
add_executable(portAudio-test ${portAudio_TEST_SRCS} ${portAudio_TEST_HDRS})
target_link_libraries(portAudio-test portaudio ${OpenCV_LIBS})
