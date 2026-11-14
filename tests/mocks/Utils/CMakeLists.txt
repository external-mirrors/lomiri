qt_add_qml_module(mockutilsplugin
    URI Utils
    VERSION 0.1
    PLUGIN_TARGET mockutilsplugin
    SOURCES
        constants.cpp
        deviceinfo.cpp
        displaycutoutsmodel.cpp
        plugin.cpp
        URLDispatcher.cpp
        windowstatestorage.cpp
        ${CMAKE_SOURCE_DIR}/plugins/Utils/activefocuslogger.cpp
        ${CMAKE_SOURCE_DIR}/plugins/Utils/appdrawerproxymodel.cpp
        ${CMAKE_SOURCE_DIR}/plugins/Utils/applicationsfiltermodel.cpp
        ${CMAKE_SOURCE_DIR}/plugins/Utils/deviceconfig.cpp
        ${CMAKE_SOURCE_DIR}/plugins/Utils/easingcurve.cpp
        ${CMAKE_SOURCE_DIR}/plugins/Utils/expressionfiltermodel.cpp
        ${CMAKE_SOURCE_DIR}/plugins/Utils/globalfunctions.cpp
        ${CMAKE_SOURCE_DIR}/plugins/Utils/inputeventgenerator.cpp
        ${CMAKE_SOURCE_DIR}/plugins/Utils/inputwatcher.cpp
        ${CMAKE_SOURCE_DIR}/plugins/Utils/lomirimenumodelpaths.cpp
        ${CMAKE_SOURCE_DIR}/plugins/Utils/lomirisortfilterproxymodelqml.cpp
        ${CMAKE_SOURCE_DIR}/plugins/Utils/qlimitproxymodelqml.cpp
        ${CMAKE_SOURCE_DIR}/plugins/Utils/quicklistproxymodel.cpp
        ${CMAKE_SOURCE_DIR}/plugins/Utils/tabfocusfence.cpp
        ${CMAKE_SOURCE_DIR}/plugins/Utils/timezoneFormatter.cpp
        ${CMAKE_SOURCE_DIR}/plugins/Utils/windowinputfilter.cpp
    QML_FILES
        EdgeBarrierSettings.qml
        Style.js
        WindowInputMonitor.qml
)

target_include_directories(mockutilsplugin PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/plugins/Utils
)

target_link_libraries(mockutilsplugin PRIVATE
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

install_qml_module(mockutilsplugin DESTINATION ${SHELL_INSTALL_QML}/mocks)
