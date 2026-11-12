foreach(source_file ${QMLPLUGIN_SRC})
    list(APPEND RELATIVE_QMLPLUGIN_SRC ../${source_file})
endforeach()

add_library(IntegratedLightDM-qml MODULE
    ${RELATIVE_QMLPLUGIN_SRC}
    )

target_include_directories(IntegratedLightDM-qml PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/plugins/Utils
)

target_compile_definitions(IntegratedLightDM-qml PRIVATE INTEGRATED_LIGHTDM)

target_link_libraries(IntegratedLightDM-qml PRIVATE
    lomiri-paths
    integratedLightDM
    lomiri-private
    PkgConfig::LIBUSERMETRICSOUTPUT
    Qt::DBus
    Qt::Gui
    Qt::Qml
)

add_lomiri_plugin(IntegratedLightDM 0.1 LightDM/IntegratedLightDM TARGETS IntegratedLightDM-qml)

add_subdirectory(liblightdm)
