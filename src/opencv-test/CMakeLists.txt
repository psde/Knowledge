set(OPENCV_TEST_SRCS
    main.cpp
	ImageProcessor.cpp
	../opencv-graph/Graph.cpp
)

set(OPENCV_TEST_HDRS
	ImageProcessor.h
	../opencv-graph/Graph.h
)

if(CMAKE_COMPILER_IS_GNUCXX)
	message(STATUS " | Detected GNUCXX")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++11 -pedantic -g")
endif()

find_package(OpenCV REQUIRED)
add_executable(opencv-test ${OPENCV_TEST_SRCS} ${OPENCV_TEST_HDRS})
target_link_libraries(opencv-test ${OpenCV_LIBS})
