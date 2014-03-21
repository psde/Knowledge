set(CORE_SRCS
    main.cpp
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

add_executable(core ${CORE_SRCS} ${CORE_HDRS})
target_link_libraries(core ${CMAKE_THREAD_LIBS_INIT})