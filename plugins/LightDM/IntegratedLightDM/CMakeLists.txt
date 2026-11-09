add_definitions(-DINTEGRATED_LIGHTDM)

include_directories(
    . #QLightDM
    ${liblomiri-private_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
)

foreach(source_file ${QMLPLUGIN_SRC})
    list(APPEND RELATIVE_QMLPLUGIN_SRC ../${source_file})
endforeach()

add_library(IntegratedLightDM-qml MODULE
    ${RELATIVE_QMLPLUGIN_SRC}
    )

target_link_libraries(IntegratedLightDM-qml PRIVATE
    integratedLightDM
    lomiri-private
    PkgConfig::LIBUSERMETRICSOUTPUT
    Qt::DBus
    Qt::Gui
    Qt::Qml
)

add_lomiri_plugin(IntegratedLightDM 0.1 LightDM/IntegratedLightDM TARGETS IntegratedLightDM-qml)

add_subdirectory(liblightdm)
