set(OPENCV_TEST_SRCS
    main.cpp
)

set(OPENCV_TEST_HDRS
)

add_executable(opencv-test ${OPENCV_TEST_SRCS} ${OPENCV_TEST_HDRS})
target_link_libraries(opencv-test ${OpenCV_LIBS})