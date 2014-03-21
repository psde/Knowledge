set(CORE_SRCS
    Consumer.cpp
    Producer.cpp
    DequeBuffer.cpp
    Data.cpp
)

set(CORE_HDRS
    Consumer.h
    Producer.h
    DequeBuffer.h
    Data.h
)

add_library(core ${CORE_SRCS} ${CORE_HDRS})
target_link_libraries(core ${CMAKE_THREAD_LIBS_INIT})