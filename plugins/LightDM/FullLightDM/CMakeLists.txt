foreach(source_file ${QMLPLUGIN_SRC})
    list(APPEND RELATIVE_QMLPLUGIN_SRC ../${source_file})
endforeach()

qt_add_qml_module(fulllightdmplugin
    URI LightDM.FullLightDM
    VERSION 0.1
    PLUGIN_TARGET fulllightdmplugin
    SOURCES ${RELATIVE_QMLPLUGIN_SRC}
)

target_include_directories(fulllightdmplugin PRIVATE ${CMAKE_SOURCE_DIR}/plugins/Utils)

target_compile_definitions(fulllightdmplugin PRIVATE FULL_LIGHTDM)

target_link_libraries(fulllightdmplugin PRIVATE
    lomiri-paths
    lomiri-private
    PkgConfig::LIBLIGHTDM
    PkgConfig::LIBUSERMETRICSOUTPUT
    Intl::Intl
    Qt::DBus
    Qt::Gui
    Qt::Qml
)

install_qml_module(fulllightdmplugin DESTINATION ${SHELL_INSTALL_QML})
