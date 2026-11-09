include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
)

set(QMLPLUGIN_SRC
    activefocuslogger.cpp
    applicationsfiltermodel.cpp
    appdrawerproxymodel.cpp
    constants.cpp
    WindowInputMonitor.cpp
    inputwatcher.cpp
    qlimitproxymodelqml.cpp
    lomirisortfilterproxymodelqml.cpp
    Timer.cpp
    lomirimenumodelpaths.cpp
    windowinputfilter.cpp
    easingcurve.cpp
    windowstatestorage.cpp
    timezoneFormatter.cpp
    inputeventgenerator.cpp
    deviceconfig.cpp
    globalfunctions.cpp
    URLDispatcher.cpp
    tabfocusfence.cpp
    expressionfiltermodel.cpp
    quicklistproxymodel.cpp
    fileio.cpp
    displaycutoutsmodel.cpp
    plugin.cpp
    )

add_library(Utils-qml SHARED
    ${QMLPLUGIN_SRC}
    )

target_link_libraries(Utils-qml
    PUBLIC
        lomiri-shell-application
        Qt::Sql
    PRIVATE
        lomiri-shell-launcher
        PkgConfig::DEVICEINFO
        Qt::Concurrent
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
set_target_properties(Utils-qml PROPERTIES COMPILE_FLAGS -fvisibility=default)

add_lomiri_plugin(Utils 0.1 Utils TARGETS Utils-qml)
