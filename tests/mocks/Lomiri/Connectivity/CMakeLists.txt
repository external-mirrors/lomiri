add_library(connectivity-qml SHARED
    networking-status.cpp
    plugin.cpp
)
target_link_libraries(connectivity-qml PRIVATE Qt::Qml)

# copy qmldir file into build directory for shadow builds
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/qmldir"
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
    )
