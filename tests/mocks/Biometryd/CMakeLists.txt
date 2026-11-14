qt_add_qml_module(mockbiometrydplugin
    URI Biometryd
    VERSION 0.0
    PLUGIN_TARGET mockbiometrydplugin
    SOURCES
        MockBiometryd.cpp
        MockDevice.cpp
        MockIdentifier.cpp
        MockObserver.cpp
        MockOperation.cpp
        plugin.cpp
)

target_link_libraries(mockbiometrydplugin PRIVATE
    Qt::Core
    Qt::Qml
    Qt::Quick
)

install_qml_module(mockbiometrydplugin DESTINATION ${SHELL_INSTALL_QML}/mocks)
