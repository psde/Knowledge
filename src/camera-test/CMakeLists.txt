set(CAMERA_TEST_SRCS
    main.cpp
    MainWindow.cpp
)

set(CAMERA_TEST_HDRS
    CameraProducer.h
    ImageConsumerProducer.h
    ImageConsumer.h
    MainWindow.h
)

set(CAMERA_TEST_UI_FILES
    ui/MainWindow.ui
)

set(CAMERA_TEST_RES_FILES
)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

QT4_WRAP_CPP(CAMERA_TEST_MOC_SRCS ${CAMERA_TEST_HDRS})
QT4_WRAP_UI(CAMERA_TEST_UI_SRCS ${CAMERA_TEST_UI_FILES})
QT4_ADD_RESOURCES(CAMERA_TEST_RESOURCE_SCRS ${CAMERA_TEST_RES_FILES})

add_executable(camera-test ${CAMERA_TEST_SRCS} ${CAMERA_TEST_HDRS} ${CAMERA_TEST_MOC_SRCS} ${CAMERA_TEST_UI_SRCS} ${CAMERA_TEST_RESOURCE_SCRS})
target_link_libraries(camera-test ${OpenCV_LIBS} ${CMAKE_THREAD_LIBS_INIT} core)
QT4_USE_MODULES(camera-test Core Gui)