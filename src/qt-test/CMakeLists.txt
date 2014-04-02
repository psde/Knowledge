set(Qt_TEST_SRCS
    main.cpp
)

set(Qt_TEST_HDRS
)

add_executable(qt-test ${Qt_TEST_SRCS} ${Qt_TEST_HDRS})
qt5_use_modules(qt-test Core Widgets)