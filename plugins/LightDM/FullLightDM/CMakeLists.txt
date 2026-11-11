add_definitions(-DFULL_LIGHTDM)

foreach(source_file ${QMLPLUGIN_SRC})
    list(APPEND RELATIVE_QMLPLUGIN_SRC ../${source_file})
endforeach()

add_library(FullLightDM-qml MODULE
    ${RELATIVE_QMLPLUGIN_SRC}
    )

target_include_directories(FullLightDM-qml PRIVATE ${CMAKE_SOURCE_DIR}/plugins/Utils)

target_link_libraries(FullLightDM-qml PRIVATE
    lomiri-private
    PkgConfig::LIBLIGHTDM
    PkgConfig::LIBUSERMETRICSOUTPUT
    Intl::Intl
    Qt::DBus
    Qt::Gui
    Qt::Qml
)

add_lomiri_plugin(FullLightDM 0.1 LightDM/FullLightDM TARGETS FullLightDM-qml)
