set(JUCE_SRCS
	src/modules/juce_audio_devices/juce_audio_devices.cpp
)

set(JUCE_HDRS
	src/modules/juce_audio_devices/juce_audio_devices.h
)

include_directories(includes)

add_library(juce ${JUCE_SRCS} ${JUCE_HDRS})
