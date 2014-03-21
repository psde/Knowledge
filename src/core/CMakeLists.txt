set(CORE_SRCS
    IConsumer.cpp
    IProducer.cpp
    DequeBuffer.cpp
    Data.cpp
)

set(CORE_HDRS
    IConsumer.h
    IProducer.h
    DequeBuffer.h
    Data.h
)

add_library(core ${CORE_SRCS} ${CORE_HDRS})
target_link_libraries(core ${CMAKE_THREAD_LIBS_INIT})