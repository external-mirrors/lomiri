set(LibLightDM_SOURCES
    Greeter.cpp
    SessionsModel.cpp
    UsersModel.cpp
    GreeterPrivate.cpp
    SessionsModelPrivate.cpp
    UsersModelPrivate.cpp
    ${CMAKE_SOURCE_DIR}/plugins/AccountsService/AccountsServiceDBusAdaptor.cpp
    ${CMAKE_SOURCE_DIR}/plugins/Utils/qvariantlistmodel.cpp
    )

add_library(integratedLightDM STATIC ${LibLightDM_SOURCES})

target_include_directories(integratedLightDM PRIVATE
    ${CMAKE_SOURCE_DIR}/plugins/AccountsService
    ${CMAKE_SOURCE_DIR}/plugins/LightDM
)

target_link_libraries(integratedLightDM PRIVATE
    PkgConfig::GLIB
    PkgConfig::LIBUSERMETRICSOUTPUT
    PkgConfig::PAM
    Qt::Concurrent
    Qt::DBus
    Qt::Gui
)

set_target_properties(integratedLightDM PROPERTIES POSITION_INDEPENDENT_CODE ON)
