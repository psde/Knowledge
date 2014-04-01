set(JUCE_TEST_SRCS
    main.cpp
)

set(JUCE_TEST_HDRS

)

include_directories(
	../JUCE/src/modules/juce_audio_devices 
	../JUCE/src/modules/juce_core 
	../JUCE/src/modules/juce_events
	../JUCE/src/modules/audio_basics)
add_executable(juce-test ${JUCE_TEST_SRCS} ${JUCE_TEST_HDRS})
target_link_libraries(juce-test juce)