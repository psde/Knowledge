set(portAudio_TEST_SRCS
	main.cpp
	sine.cpp
)

set(portAudio_TEST_HDRS
	sine.h
)

add_executable(portAudio-test ${portAudio_TEST_SRCS} ${portAudio_TEST_HDRS})
target_link_libraries(portAudio-test portaudio_static)