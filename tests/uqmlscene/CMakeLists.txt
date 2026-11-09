add_executable(uqmlscene
    main.cpp
    ${CMAKE_SOURCE_DIR}/src/DebuggingController.cpp
    )

include_directories(
    SYSTEM
    ${Qt5Quick_PRIVATE_INCLUDE_DIRS}
    ${Qt5Gui_PRIVATE_INCLUDE_DIRS}
)

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/src
    ${liblomiri-private_SOURCE_DIR}
)

target_link_libraries(uqmlscene
    Qt5::Qml Qt5::Quick Qt5::Test Qt5::DBus
    LomiriGestures
    lomiri-private
    )

install(TARGETS uqmlscene
    RUNTIME DESTINATION ${SHELL_PRIVATE_FULL_LIBEXECDIR}
    )
