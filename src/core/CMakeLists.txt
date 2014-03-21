set(CORE_SRCS
    IData.cpp
    IConsumer.cpp
    IProducer.cpp
    DequePool.cpp
)

set(CORE_HDRS
    IData.h
    IConsumer.h
    IProducer.h
    DequePool.h
)

add_library(core ${CORE_SRCS} ${CORE_HDRS})
target_link_libraries(core ${CMAKE_THREAD_LIBS_INIT})