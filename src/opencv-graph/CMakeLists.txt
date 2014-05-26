set(OPENCV_GRAPH_SRCS
    main.cpp
    Graph.cpp
)

set(OPENCV_GRAPH_HDRS
    Graph.h
)

if(CMAKE_COMPILER_IS_GNUCXX)
    message(STATUS " | Detected GNUCXX")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++11 -pedantic -g")
endif()
find_package(OpenCV REQUIRED)

add_executable(opencv-graph ${OPENCV_GRAPH_SRCS} ${OPENCV_GRAPH_HDRS})
target_link_libraries(opencv-graph ${OpenCV_LIBS})
