qt_add_qml_module(mockqofonoplugin
    URI QOfono
    VERSION 0.2
    PLUGIN_TARGET mockqofonoplugin
    SOURCES
        MockQOfono.cpp
        MockQOfonoManager.cpp
        plugin.cpp
    QML_FILES
        MockOfonoSimManager.qml
)

target_link_libraries(mockqofonoplugin PRIVATE
    Qt::Core
    Qt::Qml
    Qt::Quick
)

install_qml_module(mockqofonoplugin DESTINATION ${SHELL_INSTALL_QML}/mocks)
