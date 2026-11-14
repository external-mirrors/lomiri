qt_add_qml_module(inputinfoplugin
    URI Lomiri.InputInfo
    VERSION 0.1
    PLUGIN_TARGET inputinfoplugin
    SOURCES
        linux/qinputdeviceinfo_linux.cpp
        plugin.cpp
        qdeclarativeinputdevicemodel.cpp
        qinputinfo.cpp
)

target_include_directories(inputinfoplugin PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(inputinfoplugin PRIVATE
    PkgConfig::LIBEVDEV
    PkgConfig::LIBUDEV
    Qt::Core
    Qt::Qml
    Qt::Quick
)

install_qml_module(inputinfoplugin DESTINATION ${SHELL_INSTALL_QML})
