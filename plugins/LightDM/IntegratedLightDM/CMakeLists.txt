foreach(source_file ${QMLPLUGIN_SRC})
    list(APPEND RELATIVE_QMLPLUGIN_SRC ../${source_file})
endforeach()

qt_add_qml_module(integratedlightdmplugin
    URI LightDM.IntegratedLightDM
    VERSION 0.1
    PLUGIN_TARGET integratedlightdmplugin
    SOURCES ${RELATIVE_QMLPLUGIN_SRC}
)

target_include_directories(integratedlightdmplugin PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/plugins/Utils
)

target_compile_definitions(integratedlightdmplugin PRIVATE INTEGRATED_LIGHTDM)

target_link_libraries(integratedlightdmplugin PRIVATE
    lomiri-paths
    integratedLightDM
    lomiri-private
    PkgConfig::LIBUSERMETRICSOUTPUT
    Qt::DBus
    Qt::Gui
    Qt::Qml
)

install_qml_module(integratedlightdmplugin DESTINATION ${SHELL_INSTALL_QML})

add_subdirectory(liblightdm)
