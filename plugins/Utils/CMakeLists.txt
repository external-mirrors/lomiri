add_library(lomiriutilsplugin MODULE plugin.cpp)
qt_add_qml_module(lomiriutils STATIC
    URI Utils
    VERSION 0.1
    PLUGIN_TARGET lomiriutilsplugin
    SOURCES
        activefocuslogger.cpp
        appdrawerproxymodel.cpp
        applicationsfiltermodel.cpp
        constants.cpp
        deviceconfig.cpp
        displaycutoutsmodel.cpp
        easingcurve.cpp
        expressionfiltermodel.cpp
        fileio.cpp
        globalfunctions.cpp
        inputeventgenerator.cpp
        inputwatcher.cpp
        lomirimenumodelpaths.cpp
        lomirisortfilterproxymodelqml.cpp
        qlimitproxymodelqml.cpp
        quicklistproxymodel.cpp
        tabfocusfence.cpp
        Timer.cpp
        timezoneFormatter.cpp
        URLDispatcher.cpp
        windowinputfilter.cpp
        WindowInputMonitor.cpp
        windowstatestorage.cpp
    QML_FILES
        EdgeBarrierSettings.qml
        Style.js
)

target_include_directories(lomiriutils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(lomiriutils
    PUBLIC
        lomiri-shell-application
        lomiri-shell-launcher
        Qt::Qml
        Qt::Quick
        Qt::Sql
    PRIVATE
        PkgConfig::DEVICEINFO
        Qt::Concurrent
        Qt::DBus
        Qt::Gui
        Qt::GuiPrivate
        Qt::Network
        Qt::QuickPrivate
)

target_link_libraries(lomiriutilsplugin PRIVATE Qt::DBus)

install_qml_module(lomiriutils DESTINATION ${SHELL_INSTALL_QML})
