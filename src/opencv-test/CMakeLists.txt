set(OPENCV_TEST_SRCS
    main.cpp
	ImageProcessor.cpp
	../opencv-graph/Graph.cpp
)

set(OPENCV_TEST_HDRS
	ImageProcessor.h
	../opencv-graph/Graph.h
)

add_executable(opencv-test ${OPENCV_TEST_SRCS} ${OPENCV_TEST_HDRS})
target_link_libraries(opencv-test ${OpenCV_LIBS})