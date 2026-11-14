qt_add_qml_module(mockqtmultimediaplugin
    URI QtMultimedia
    VERSION 5.0
    PLUGIN_TARGET mockqtmultimediaplugin
    SOURCES
        declarativeplaylist.cpp
        mediaplayer.cpp
        plugin.cpp
        videooutput.cpp
    QML_FILES
        VideoSurface.qml
)

target_link_libraries(mockqtmultimediaplugin PRIVATE
    lomiri-paths
    Qt::Qml
    Qt::Quick
)

install_qml_module(mockqtmultimediaplugin DESTINATION ${SHELL_INSTALL_QML}/mocks)
