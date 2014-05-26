set(CORE_SRCS
	Component.cpp
)

set(CORE_HDRS
    DequePool.h
	Component.h
    Producer.h
    Consumer.h
    ConsumerProducer.h
)

add_library(core ${CORE_SRCS} ${CORE_HDRS})
target_link_libraries(core ${CMAKE_THREAD_LIBS_INIT})