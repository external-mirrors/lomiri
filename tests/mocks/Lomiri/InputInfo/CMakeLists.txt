qt_add_qml_module(mockinputinfoplugin
    URI Lomiri.InputInfo
    VERSION 0.1
    PLUGIN_TARGET mockinputinfoplugin
    SOURCES
        mockcontroller.cpp
        plugin.cpp
        qinputdeviceinfo_mock.cpp
        ${CMAKE_SOURCE_DIR}/plugins/Lomiri/InputInfo/qdeclarativeinputdevicemodel.cpp
        ${CMAKE_SOURCE_DIR}/plugins/Lomiri/InputInfo/qinputinfo.cpp
)

target_include_directories(mockinputinfoplugin PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/plugins/Lomiri/InputInfo
)

target_compile_definitions(mockinputinfoplugin PRIVATE LOMIRI_MOCKS)

target_link_libraries(mockinputinfoplugin PRIVATE
    lomiri-paths
    Qt::Core
    Qt::Qml
    Qt::Quick
)

install_qml_module(mockinputinfoplugin DESTINATION ${SHELL_INSTALL_QML}/mocks)
