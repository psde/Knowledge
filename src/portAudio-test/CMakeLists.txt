set(portAudio_TEST_SRCS
	main.cpp
	sine.cpp
	record.cpp
)

set(portAudio_TEST_HDRS
	sine.h
	record.h
	split.h
)

add_executable(portAudio-test ${portAudio_TEST_SRCS} ${portAudio_TEST_HDRS})
target_link_libraries(portAudio-test portaudio)