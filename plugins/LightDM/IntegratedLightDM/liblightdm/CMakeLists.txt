pkg_check_modules(LIBUSERMETRICSOUTPUT REQUIRED libusermetricsoutput-1)

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
add_library(integratedLightDMSession STATIC ${LibLightDM_SOURCES})

include_directories(
    ${CMAKE_SOURCE_DIR}/plugins/AccountsService
    ${CMAKE_CURRENT_BINARY_DIR}
    ${GLIB_INCLUDE_DIRS}
    ${LIBUSERMETRICSOUTPUT_INCLUDE_DIRS}
)

target_link_libraries(integratedLightDM
    ${GLIB_LIBRARIES}
    ${LIBUSERMETRICSOUTPUT_LDFLAGS}
    -lpam
    Qt5::Concurrent Qt5::DBus Qt5::Gui
)
target_link_libraries(integratedLightDMSession
    ${GLIB_LIBRARIES}
    ${LIBUSERMETRICSOUTPUT_LDFLAGS}
    -lpam
    Qt5::Concurrent Qt5::DBus Qt5::Gui
)

set_target_properties(integratedLightDM PROPERTIES
                      COMPILE_FLAGS "-DSM_BUSNAME=systemBus -fPIC")
set_target_properties(integratedLightDMSession PROPERTIES
                      COMPILE_FLAGS "-DSM_BUSNAME=sessionBus -fPIC")
