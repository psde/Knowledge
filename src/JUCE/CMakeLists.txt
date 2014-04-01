set(JUCE_SRCS
	src/modules/juce_audio_devices/juce_audio_devices.cpp
	src/modules/juce_core/juce_core.cpp
	src/modules/juce_events/juce_events.cpp
	src/modules/juce_audio_basics/juce_audio_basics.cpp
	
)

set(JUCE_HDRS
	src/modules/juce_audio_devices/juce_audio_devices.h
	src/modules/juce_core/juce_core.h
	src/modules/juce_events/juce_events.h
	src/modules/juce_audio_basics/juce_audio_basics.h
	
)

include_directories(includes)

add_library(juce ${JUCE_SRCS} ${JUCE_HDRS})
