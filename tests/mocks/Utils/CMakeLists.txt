include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/plugins/Utils
)

set(QMLPLUGIN_SRC
    ${CMAKE_SOURCE_DIR}/plugins/Utils/activefocuslogger.cpp
    ${CMAKE_SOURCE_DIR}/plugins/Utils/qlimitproxymodelqml.cpp
    ${CMAKE_SOURCE_DIR}/plugins/Utils/lomirisortfilterproxymodelqml.cpp
    ${CMAKE_SOURCE_DIR}/plugins/Utils/lomirimenumodelpaths.cpp
    ${CMAKE_SOURCE_DIR}/plugins/Utils/windowinputfilter.cpp
    ${CMAKE_SOURCE_DIR}/plugins/Utils/easingcurve.cpp
    ${CMAKE_SOURCE_DIR}/plugins/Utils/inputwatcher.cpp
    ${CMAKE_SOURCE_DIR}/plugins/Utils/timezoneFormatter.cpp
    ${CMAKE_SOURCE_DIR}/plugins/Utils/applicationsfiltermodel.cpp
    ${CMAKE_SOURCE_DIR}/plugins/Utils/inputeventgenerator.cpp
    ${CMAKE_SOURCE_DIR}/plugins/Utils/deviceconfig.cpp
    ${CMAKE_SOURCE_DIR}/plugins/Utils/globalfunctions.cpp
    ${CMAKE_SOURCE_DIR}/plugins/Utils/appdrawerproxymodel.cpp
    ${CMAKE_SOURCE_DIR}/plugins/Utils/tabfocusfence.cpp
    ${CMAKE_SOURCE_DIR}/plugins/Utils/expressionfiltermodel.cpp
    ${CMAKE_SOURCE_DIR}/plugins/Utils/quicklistproxymodel.cpp
    constants.cpp
    plugin.cpp
    windowstatestorage.cpp
    URLDispatcher.cpp
    deviceinfo.cpp
    displaycutoutsmodel.cpp
    )

add_library(FakeUtils-qml SHARED
    ${QMLPLUGIN_SRC}
    )

target_link_libraries(FakeUtils-qml PRIVATE
    lomiri-shell-application
    lomiri-shell-launcher
    PkgConfig::GIO
    Qt::DBus
    Qt::Gui
    Qt::GuiPrivate
    Qt::Network
    Qt::Qml
    Qt::Quick
    Qt::QuickPrivate
)

# Because this is an internal support library, we want
# to expose all symbols in it. Consider changing this
# either to a static library or just using the
# files directly in targets.
set_target_properties(FakeUtils-qml PROPERTIES COMPILE_FLAGS -fvisibility=default)

add_lomiri_mock(Utils 0.1 Utils TARGETS FakeUtils-qml)
