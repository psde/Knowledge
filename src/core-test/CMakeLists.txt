set(CORE_TEST_SRCS
    main.cpp
)

set(CORE_TEST_HDRS
	IntConsumeTest.h
)

add_executable(core-test ${CORE_TEST_SRCS} ${CORE_TEST_HDRS})
target_link_libraries(core-test ${CMAKE_THREAD_LIBS_INIT} core)