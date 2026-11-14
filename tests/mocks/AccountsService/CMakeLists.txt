qt_add_qml_module(mockaccountsserviceplugin
    URI AccountsService
    VERSION 0.1
    PLUGIN_TARGET mockaccountsserviceplugin
    SOURCES
        AccountsService.cpp
        plugin.cpp
        ${CMAKE_SOURCE_DIR}/plugins/LightDM/Greeter.cpp
        ${CMAKE_SOURCE_DIR}/plugins/LightDM/PromptsModel.cpp
        ${CMAKE_SOURCE_DIR}/plugins/LightDM/UsersModel.cpp
        ${CMAKE_SOURCE_DIR}/plugins/Utils/lomirisortfilterproxymodelqml.cpp
)

target_include_directories(mockaccountsserviceplugin PRIVATE
    ${CMAKE_SOURCE_DIR}/plugins/LightDM
    ${CMAKE_SOURCE_DIR}/plugins/LightDM/IntegratedLightDM
    ${CMAKE_SOURCE_DIR}/plugins/Utils
)

target_link_libraries(mockaccountsserviceplugin PRIVATE
    lomiri-paths
    MockLightDM
    Intl::Intl
    Qt::DBus
    Qt::Qml
)

install_qml_module(mockaccountsserviceplugin DESTINATION ${SHELL_INSTALL_QML}/mocks)
